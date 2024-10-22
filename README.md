# About

pappa (derived from "発破") is a bit-crusher, which is inspired some nice gadgets such as OTO Machines' Biscuit or Bastl Instruments' XOR. It is also released on [Gumroad](https://xinisnot.gumroad.com/l/lulu). If you like it, I would appreciate if you can leave a small tip.

# How to build

pappa is made with JUCE (GUI) and Faust (DSP). After installing JUCE and Faust, generate `Pappa.Dsp.h` in `/dsp` with following command. This is header-only class for DSP which is included in `PluginProcessor.h`.

```
$ cd dsp
$ faust -i -a arch.h pappa.dsp -o PappaDsp.h 
```

Then, open `Pappa.jucer` JUCE project file, create a appropriate export target if necessary. All that's left is to build plug-ins on your IDE.