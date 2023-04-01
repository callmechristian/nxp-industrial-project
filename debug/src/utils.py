import math

def sine_signal(amplitude, frequency, phase, sampling_rate, time):

    # Calculate the time between samples
    dt = 1 / sampling_rate

    # Generate the signal samples
    t = time * dt  # Calculate the time of the current sample
    sample = amplitude * math.sin(2 * math.pi * frequency * t + phase)  # Calculate the value of the sine wave at this time

    return sample