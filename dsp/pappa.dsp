declare filename "pappa.dsp";
declare name "pappa";
import("stdfaust.lib");

// ui and params
bitFlip     = vslider("[0]flip[style:knob]",                0,  0,    255, 1);
bitMute     = vslider("[1]mute[style:knob]",                0,  0,    255, 1);
fbAmount    = vslider("[2]feedback[style:knob][unit:dB]",   -70, -70, 36,  0.001) : ba.db2linear : si.smoo;
fbCutoff    = vslider("[3]cutoff[style:knob]",              0,  0,    1,   0.001) : si.smoo;
fbQ         = vslider("[4]q[style:knob]",                   0,  0,    25,  0.001) : si.smoo;

// effects
nonlinearFeedback(amount, cutoff, res, x)
    = x
    : saturation(amount)
    : filter(cutoff, res)
    : fi.dcblocker
with {
    saturation(amount, x)   = (amount, x) : * : ma.tanh;
    filter(cutoff, res, x)  = x : ve.moogHalfLadder(cutoff, res);
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

pappa(x) = ((x, _) : + : bitwiseOp(bitFlip, bitMute)) ~ (_@(ma.BS) : nonlinearFeedback(fbAmount, fbCutoff, fbQ));

process = _, _ :  pappa, pappa;