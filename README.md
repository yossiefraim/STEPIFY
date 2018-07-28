# STEPIFY
Arduino Pedometer with Led Bracelet

A device for pre-define a daily steps that communicates with a Led bracelet for positive Feedback regarding achieved steps


With the bracelet device we set the desired amount of daily steps that we want to achieve.

The bracelet sends the required steps amount to the shoe device that counts the achieved steps and send a message every requiredSteps/10 steps.

Every message represented as one light bulb on the bracelet.

The acknowledgement divided to 3 parts:

•	Red lights represent the first third of steps
•	Yellow for the second third 
•	Green lights for the last third.

At the point that the required daily steps reached the bracelet will blink all over with green lights.
