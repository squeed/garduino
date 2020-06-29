# Garduino

A silly little garden-bot with some fun features:

* Hysteresis
* Reasonable delay
* Resistive sensor preservation.

In general, most plants don't want to live in permanently wet soil. Roots need to aspirate as well. Most "garden-bots" just water constantly until a desired level is reached.

This code does not. It has some simple hysteresis so that the soil first dries out, then is properly watered. That lessens the chance of mold and makes your little roots happy.

This also has a simple trick for preserving resistive soil moisture sensors. Rather than always passing current through them, and thus encouraging electrolysis, it keeps both pins tied to ground. This works because ATMega will let you use analog pins as outputs. When it comes time to measure, they are turned back in to input pins.

You don't need any other components - you can wire the soil moisture sensor directly to the ground and analog pins.
