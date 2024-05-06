import("stdfaust.lib");

// ui and params

fxGroup(x)  = hgroup("[0]fx", x);
bitGroup(x) = fxGroup(hgroup("[0]bitwise operation", x));
fbGroup(x)  = fxGroup(hgroup("[1]feedback", x));
bypass      = fxGroup(checkbox("[2]bypass"));

bitFlip  = bitGroup(vslider("[0]flip", 0, 0, 255, 1));
bitMute  = bitGroup(vslider("[1]mute", 0, 0, 255, 1));
fbType   = fbGroup (vslider("[0]type",      0,   0,     2, 1));
fbAmount = fbGroup (vslider("[1]feedback",  0,  -2,     2, 0.001)) : si.smoo;
fbCutoff = fbGroup (vslider("[2]cutoff",    400, 0, 22050, 0.001)) : si.smoo;
fbRes    = fbGroup (vslider("[3]resonance", 0.5, 0,     1, 0.001)) : si.smoo;

// effects

nonlinearFeedback(type, amount, cutoff, res, x)
    = x
    : saturation(amount)
    : filter(type, cutoff, res)
    : fi.dcblocker
with {
    saturation(amount, x) = (amount, x) : * : ma.tanh;
    filter(type, cutoff, res, x) = x <: fi.svf.lp(cutoff, res), fi.svf.hp(cutoff, res), fi.svf.bp(cutoff, res) : select3(type);
};

bitwiseOp(xorAmt, andAmt, x)
    = x : to8bit
    : (_, xorAmt) : xor
    : (_, amount) : &
    : from8bit : (_, offset) : + : (_, scale) : *
with {
    to8bit(x)   = (x, 1)      : + : (_, 127.5) : * : int;
    from8bit(x) = (x, 127.5)  : / : (_, 1)     : -;

    amount = (255, andAmt) : -;
    offset = (andAmt, 255) : /;
    scale  = (amount, 255)  : select2(amount == 0) : (255, _) : /;
};

// process

process = _, _ :  pappa
with {
    pappaMono(x)
        = ((x, _) : + : bitwiseOp(bitFlip, bitMute))
        ~ (_@(ma.BS) : nonlinearFeedback(fbType, fbAmount, fbCutoff, fbRes));

    pappa = _, _ : ba.bypass2(bypass, (pappaMono, pappaMono));
};