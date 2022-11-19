from machine import Pin
from utime import sleep_ms
from liquid_crystal_pico import LiquidCrystalPico

# sleep_ms(5000)

led_pin = Pin(25, Pin.OUT)
led_pin.value(0)

print("hello worlds")

# lcm = LCM(3, 5, 10, 11, 12, 13)

rs = Pin(13, Pin.OUT)
rs.value(0)
sleep_ms(1)
rs.value(1)
sleep_ms(1)
rs.value(0)
sleep_ms(1)

rw = Pin(12, Pin.OUT)
rw.value(0)
e  = Pin(11, Pin.OUT)
d4 = Pin(6, Pin.OUT)
d5 = Pin(5, Pin.OUT)
d6 = Pin(4, Pin.OUT)
d7 = Pin(3, Pin.OUT)

lcd = LiquidCrystalPico(rs, e, d4, d5, d6, d7)
# lcd.clear()
# lcd.move_to(0,1)
# lcd.write("Hello Python!")

led_pin.value(1)
print("done.")


# while True:
    # pass