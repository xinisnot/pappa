import("stdfaust.lib");

ui_or     = nentry("or",  0, 0, 254, 1);
ui_and    = nentry("and", 0, 0, 254, 1);
ui_xor    = nentry("xor", 0, 0, 255, 1);
ui_del    = nentry("delay",    0,   0, 0.1, 0.00000001) : si.smoo;
ui_fb     = nentry("feedback", 0,   0, 1,   0.00000001) : si.smoo;
ui_cutoff = nentry("cutoff",   1,   0, 1,   0.00000001) : si.smoo;
ui_q      = nentry("q",        0,   0, 25,  0.00000001) : si.smoo;
ui_gain   = nentry("gain",     0, -70, 12,  0.00000001) : ba.db2linear : si.smoo;
ui_bypass = checkbox("bypass");


//============================================================================================
// functions

bipolar2eightBit(x) = int((x+1)*127.5);
eightBit2bipolar(x) = x/127.5 - 1;

biscuitXOR(arg_amt, x) = x : bipolar2eightBit : xor(arg_amt) : eightBit2bipolar;
biscuitAND(arg_amt, x) = x : bipolar2eightBit : &(p_amt) : eightBit2bipolar : +(p_offset) : *(p_scale)
with {
    p_amt = 255 - arg_amt;
    p_offset = arg_amt / 255;
    p_scale  = 255 / select2(p_amt==0, p_amt, 255);
};
biscuitOR(arg_amt, x) = x : bipolar2eightBit : |(arg_amt) : eightBit2bipolar : +(p_offset) : *(p_scale)
with {
    p_offset = -arg_amt / 255;
    p_scale  = 255/select2(arg_amt==255, 255-arg_amt, 255);
};

biscuit(arg_amtOR, arg_amtAND, arg_amtXOR, x) = x : biscuitXOR(arg_amtXOR) : biscuitAND(arg_amtAND) : biscuitOR(arg_amtOR);

delayLine(arg_maxDur, arg_dur, arg_gain, x) = x@(min(p_maxDur, max(0, p_dur))) : *(arg_gain)
with
{
    p_maxDur = ma.SR * arg_maxDur;
    p_dur    = ma.SR * arg_dur;
};



//============================================================================================
// main loop

fx = (biscuit(ui_or, ui_and, ui_xor, +(_)) : ve.moogLadder(ui_cutoff, ui_q)) ~ delayLine(1, ui_del, ui_fb);

process = _, _ : ba.bypass2(ui_bypass, (fx, fx)) : *(ui_gain), *(ui_gain);