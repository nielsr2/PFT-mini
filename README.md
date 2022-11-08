Hall-effect foot expression pedal

Niels
Prototyping and Fabrication Techniques
November 2022

![](https://i.imgur.com/PB5k93O.jpg)

![](wobble.gif)

## Parts overview

Microcontroller: Daisy Seed

Software / platform: Max MSP gen via Oopsy,

Component List
- Linear Hall-effect sensor
- Neodymium magnets
- 2x jack mono plugs
- 1PST momentary footswitch soft short

Materials: Various woods, and acryllic. Parts are glued together, or uses screws.

Illustrator have been used for all laser cutting and most design.


## Motivation

- Expression pedal design are generally pretty uniform and boring.
	- They are limited to one axis, and mechanical gears & potentiometers.
- Fancier MIDI exists, but are 1) expensive, 2) made for different use-cases.


## Related work

As Physical Interface Design course mini-project, the idea was originally pursued with the hacking of a Roland EV-5 pedal. This leveraged the existing pinion and rack gear design.

Other related work include design implemented as part of a shoe.
See Konovalovs, K., Zovnercuka, J., Adjorlu, A., & Overholt, D. (2017, May). A wearable foot-mounted/instrument-mounted effect controller: Design and evaluation. In New Interfaces for Musical Expression 2017 (pp. 354-357). NIME.

## Design process


Parallel with the design of the hardware, The design process vs breadboard. The breadboard work is only documented through code, see gen-patches.


#### Wheel design

In order to achieve an additional axis for rotation, wheels from hardware stores were investigated and were considered for the design for the majority of the project. Flipping the wheel upside down allows attaching a footpedal top, that can also rotate.
![](https://i.imgur.com/pGMbqQR.png)
[PN Beslag, Møbelhjul m. plade, Ø: 51 x H: 66 mm -](https://www.silvan.dk/pn-moebelhjul-med-plade?id=2760-1251239)


Various wheels were considered and designed for, from the tiny and flimsy, to the massive and brutalistic.

![](https://i.imgur.com/eC3EHSn.jpg)

![](https://i.imgur.com/sfQvnpU.jpg)

There's some downsides to this design however. The sturdiest wheel (while not being too massive), still could get bent out of shape. Furthermore, it was found hard to implement a physical barrier at the extremes of pedal positions. With this design, it would need to be implemented as part of the wheel, as to still provide a limit when rotating on the two axes.

The various wheel designs, and difficulty cutting accurate parts to fit, resulted in this design being abandoned.

![](https://i.imgur.com/GuTaZHk.jpg)
![](https://i.imgur.com/dGFqr98.jpg)

Above is seen an attempt to create a sturdier base in order to provide resistance/limits to the pedal.
CONS:
- raises the height of the pedal top
- Never found ideal wheel
- Problem of reliable, sturdy
#### One-screw design

This design sought to simplify the mechanics, while maintain Simplyfying the design, seeked to

Using an elipse provides space for the screw moving. The approximate size needed was done
![](https://i.imgur.com/E767WKZ.jpg)
Note: the image is just to document how vizualisation was done in illustrator as part of the design process. The actual laser cut and simulation for the mechanic were performed on the lab machine (because it was depending on thickness of materials)

![](screw.gif)


Pros:
- The mechanism provides haptic feedback
- provides a secure footing

Cons:
- Might jam
- Will break with time
- Produces sound

#### new design: separate top and bottom.

Pros:
* Mechanical breakdown less likely
* Modular design - Change out top - Change tip balance, Visual aesthetic
* Lower pedal height, and more flexible use of space
* Flexible & Extendable design (see [[#Future Directions]])
* Emphasizes the balance and feel of the pedal by direct surface contact and t

Cons:
* Introduces more varied and noisy Hall effect sensor data that requires futher attention.
* Scratches the surface.

## Visual identity / Design Aesthetic

Many the effect pedals and pedal boards consist of black plastic, metal, and rubber parts. For good and bad, this produces products with the a sleek aesthetic of mass manufactured tanks.

Limited to the possibilities at hand (i.e., no metal work), a more old school ornamented look was opted for.

A dark solid wood tabletop were used main enclosure. Glued and stacked wooden rectangles form the backside. Acryllic panels featuring ornaments and holes form the sides.

All ornamentation is taken from:
Jablan, S. V. (2002). _Symmetry, ornament and modularity_ (Vol. 30). World Scientific.


#### Pedal Grip Design

The top part of the pedal requires friction-promoting design in order to avoid slippage.

The design is inspired by the friction ridges of our fingers.

Various ways were considered, and the most straightforward was chosen. While real fingerprints would potentially be the visually most interesting, it is also a bit of a time-consuming task to get a good print, and clean up the images and vectors. Means of generating synthetic fingerprints (1)[Biometric System Laboratory](http://biolab.csr.unibo.it/research.asp?organize=Activities&select=&selObj=12&pathSubj=111%7C%7C12&), (2)[[Anguli](https://dsl.cds.iisc.ac.in/projects/Anguli/userguide.html)] were considered, however a more simple solution were choosen [Shader - Shadertoy BETA](https://www.shadertoy.com/view/4t3SWN)

Because it is generative, each pedaltop could have a unique design.

![](https://i.imgur.com/0j9vXhe.png)

The cut surface is glued to another surface.


## Software

The software is made in Max/MSP's Gen environment and ported to the Daisy Platform using Oopsy.

While the hardware can support various types of effect, the implemented effect is a stutter-effect. This is effect is an old personal project, that has been included to as a possible use-case scenario.  

When one of the extremes of the pedal axes is reached, a buffer begins recording for x note length, and the looping that recording until which is subsequently looped until the extreme of axis is left. The loop-lengths are manually set according to a BPM.

![](https://i.imgur.com/B4NMMSS.png)

### Gen Patch

#### Hall Effect Sensor Input processing.

Oopsy provides LP-filter implementation *oopsy.ctrl.smooth2* that work quite nicely. However, as per component specifications, a ceramic 0.01 µ Farad ceramic capacitor should be added between VCC and ground, and would further smooth the signal.

Normalizing of sensor input is heavily inspired by a Max-provided gen-implementation of *minmax~*. The input is then scaled according to the needs.

![](https://i.imgur.com/WIiClLu.png)

#### Debugging

Since there is no means of communication between Max and the Daisy platform, other than uploading code, sensor and circuit-checks were troubleshooted by feeding the signal into an audio interface, and visualizing the sensor data with a spectrogram.

![](https://i.imgur.com/O5J73Qm.png)

![](ezgif-4-403d79d484)

Next steps:
implement button to reset minmax's on sensor in order to calibrate minimum. Solder second hall effect sensor, another output.

## Future Directions

Most critical:
- Tweak pedal balance, and tipping points.
- Magnets strengths and positions.
- Communication between device and computer.
	- Change effect settings (i.e., stutter lengths, BPM)
	- Change between effects, record activity, visualize activity )
-

New Design consideration:

A merge between the last two design iterations could potentially serve the best of both worlds - Steadyness, and freedom to move around the surface. A mechanism to lock/unlock should be possible. Conducive tape could be used in several ways - for specific pedal position, and as a pressure sensor.  

- I should've documented various prototypes with video/pictures - successes, and failures.
- Used Fusion 360 more. Because of the initial wheel designs, which were more work to sufficiently replicate in 3D. Fusion 360 could be used for future The simplified design would benefit

---

"Gears" / Positions
Tape - Force
OLED display (for visual feedback on timing)
Conversion from Line-level to instrument-level & vice versa. Bypassing the need to a preamp/reamper/DI-box.


---
## Appendix
Eagle schematic

![](https://i.imgur.com/ay8upFx.png)

Note the folders /Eagle, /Illustrator, and /Max for files.
