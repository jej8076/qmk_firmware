#!/usr/bin/env python3
"""Generate cute dog pixel art frames for 128x32 SSD1306 OLED."""

import math

W, H = 128, 32

def new_frame():
    return [[0]*W for _ in range(H)]

def set_pixel(frame, x, y):
    if 0 <= x < W and 0 <= y < H:
        frame[y][x] = 1

def fill_circle(frame, cx, cy, r):
    for y in range(max(0, cy-r), min(H, cy+r+1)):
        for x in range(max(0, cx-r), min(W, cx+r+1)):
            if (x-cx)**2 + (y-cy)**2 <= r*r:
                set_pixel(frame, x, y)

def fill_ellipse(frame, cx, cy, rx, ry):
    for y in range(max(0, cy-ry), min(H, cy+ry+1)):
        for x in range(max(0, cx-rx), min(W, cx+rx+1)):
            if ((x-cx)/rx)**2 + ((y-cy)/ry)**2 <= 1.0:
                set_pixel(frame, x, y)

def fill_rect(frame, x1, y1, x2, y2):
    for y in range(max(0, y1), min(H, y2+1)):
        for x in range(max(0, x1), min(W, x2+1)):
            set_pixel(frame, x, y)

def fill_triangle(frame, x1, y1, x2, y2, x3, y3):
    min_y = max(0, min(y1, y2, y3))
    max_y = min(H-1, max(y1, y2, y3))
    min_x = max(0, min(x1, x2, x3))
    max_x = min(W-1, max(x1, x2, x3))
    def sign(px, py, ax, ay, bx, by):
        return (px-bx)*(ay-by) - (ax-bx)*(py-by)
    for y in range(min_y, max_y+1):
        for x in range(min_x, max_x+1):
            d1 = sign(x, y, x1, y1, x2, y2)
            d2 = sign(x, y, x2, y2, x3, y3)
            d3 = sign(x, y, x3, y3, x1, y1)
            has_neg = (d1 < 0) or (d2 < 0) or (d3 < 0)
            has_pos = (d1 > 0) or (d2 > 0) or (d3 > 0)
            if not (has_neg and has_pos):
                set_pixel(frame, x, y)

def clear_circle(frame, cx, cy, r):
    for y in range(max(0, cy-r), min(H, cy+r+1)):
        for x in range(max(0, cx-r), min(W, cx+r+1)):
            if (x-cx)**2 + (y-cy)**2 <= r*r:
                if 0 <= x < W and 0 <= y < H:
                    frame[y][x] = 0

def clear_rect(frame, x1, y1, x2, y2):
    for y in range(max(0, y1), min(H, y2+1)):
        for x in range(max(0, x1), min(W, x2+1)):
            frame[y][x] = 0

def draw_line(frame, x1, y1, x2, y2):
    dx = abs(x2-x1)
    dy = abs(y2-y1)
    sx = 1 if x1 < x2 else -1
    sy = 1 if y1 < y2 else -1
    err = dx - dy
    while True:
        set_pixel(frame, x1, y1)
        if x1 == x2 and y1 == y2:
            break
        e2 = 2*err
        if e2 > -dy:
            err -= dy
            x1 += sx
        if e2 < dx:
            err += dx
            y1 += sy

def draw_dog_base(frame):
    """Draw the base dog shape - a cute sitting dog facing right."""
    # Body - oval, slightly tilted
    fill_ellipse(frame, 60, 20, 16, 10)

    # Head - circle
    fill_circle(frame, 82, 12, 9)

    # Neck connection
    fill_ellipse(frame, 72, 16, 8, 6)

    # Snout/muzzle - small oval protruding right
    fill_ellipse(frame, 92, 14, 5, 4)

    # Nose - small dark circle at tip of snout (will be "cleared" as it's white-on-black)
    # Actually for monochrome OLED, 1=lit. Let's keep nose as a bump.
    # Clear inside of nose tip for detail
    clear_circle(frame, 96, 13, 1)

    # Eye - clear a small circle for the eye (dark on light head)
    clear_circle(frame, 85, 10, 2)
    # Eye pupil
    set_pixel(frame, 85, 10)
    set_pixel(frame, 86, 10)

    # Left ear (far ear) - triangle
    fill_triangle(frame, 74, 12, 76, 1, 80, 6)

    # Right ear (near ear) - triangle
    fill_triangle(frame, 82, 8, 86, 0, 90, 5)

    # Front legs
    fill_rect(frame, 70, 26, 74, 31)
    fill_rect(frame, 76, 26, 80, 31)

    # Back legs (sitting, tucked)
    fill_ellipse(frame, 50, 26, 6, 4)
    fill_rect(frame, 46, 28, 50, 31)

    # Mouth line
    draw_line(frame, 92, 16, 95, 16)

    # Paw details - small lines at bottom of front legs
    set_pixel(frame, 69, 31)
    set_pixel(frame, 81, 31)

    # Belly curve - clear a small area under body for shape
    # Add a small collar detail
    fill_rect(frame, 74, 17, 76, 19)
    clear_rect(frame, 75, 17, 75, 19)

def draw_tail(frame, position):
    """Draw tail in different positions: 'left', 'center', 'right'"""
    if position == 'left':
        # Tail curving up-left
        fill_triangle(frame, 44, 18, 38, 8, 42, 12)
        fill_ellipse(frame, 39, 9, 3, 2)
    elif position == 'center':
        # Tail straight up
        fill_triangle(frame, 44, 18, 40, 6, 44, 10)
        fill_ellipse(frame, 41, 7, 3, 2)
    elif position == 'right':
        # Tail curving up-right
        fill_triangle(frame, 44, 18, 42, 8, 46, 10)
        fill_ellipse(frame, 43, 8, 3, 2)

def draw_dog_typing_base(frame):
    """Draw dog in typing pose - slightly leaning forward with paws on keyboard."""
    # Body - oval, slightly more forward-leaning
    fill_ellipse(frame, 58, 18, 16, 10)

    # Head - circle, slightly lower (looking at keyboard)
    fill_circle(frame, 82, 13, 9)

    # Neck connection
    fill_ellipse(frame, 72, 15, 8, 6)

    # Snout/muzzle
    fill_ellipse(frame, 92, 15, 5, 4)

    # Nose detail
    clear_circle(frame, 96, 14, 1)

    # Eye - looking down
    clear_circle(frame, 85, 11, 2)
    set_pixel(frame, 85, 12)
    set_pixel(frame, 86, 12)

    # Left ear - slightly back
    fill_triangle(frame, 74, 13, 76, 2, 80, 7)

    # Right ear
    fill_triangle(frame, 82, 9, 86, 1, 90, 6)

    # Keyboard/surface in front
    fill_rect(frame, 72, 27, 98, 29)
    # Keyboard keys detail
    clear_rect(frame, 77, 28, 77, 28)
    clear_rect(frame, 82, 28, 82, 28)
    clear_rect(frame, 87, 28, 87, 28)
    clear_rect(frame, 92, 28, 92, 28)

    # Back legs (sitting)
    fill_ellipse(frame, 48, 24, 6, 4)
    fill_rect(frame, 44, 27, 48, 31)

    # Tail - straight up (focused)
    fill_triangle(frame, 42, 16, 38, 4, 42, 8)
    fill_ellipse(frame, 39, 5, 3, 2)

    # Mouth
    draw_line(frame, 92, 17, 95, 17)

    # Collar
    fill_rect(frame, 74, 18, 76, 20)
    clear_rect(frame, 75, 18, 75, 20)

    # Ground line
    draw_line(frame, 30, 31, 110, 31)

def draw_typing_paws(frame, left_down):
    """Draw typing paws - alternating which paw is pressing down."""
    if left_down:
        # Left paw down (pressing key)
        fill_rect(frame, 72, 23, 76, 27)
        # Right paw up
        fill_rect(frame, 80, 21, 84, 27)
        # Small impact lines on left
        set_pixel(frame, 74, 29)
    else:
        # Left paw up
        fill_rect(frame, 72, 21, 76, 27)
        # Right paw down (pressing key)
        fill_rect(frame, 80, 23, 84, 27)
        # Small impact lines on right
        set_pixel(frame, 82, 29)

def frame_to_bytes(frame):
    """Convert 32x128 pixel grid to 512 SSD1306 bytes."""
    result = []
    for page in range(4):
        for col in range(W):
            byte = 0
            for bit in range(8):
                row = page * 8 + bit
                if frame[row][col]:
                    byte |= (1 << bit)
            result.append(byte)
    return result

def bytes_to_c_array(data, name):
    """Convert byte list to C PROGMEM array string."""
    lines = [f"static const char PROGMEM {name}[] = {{"]
    for i in range(0, len(data), 16):
        chunk = data[i:i+16]
        hex_str = ", ".join(f"0x{b:02x}" for b in chunk)
        if i + 16 < len(data):
            hex_str += ","
        lines.append(f"    {hex_str}")
    lines.append("};")
    return "\n".join(lines)

def print_frame_preview(frame):
    """Print ASCII preview of frame."""
    for y in range(H):
        row = ""
        for x in range(0, W, 2):  # Sample every 2 pixels for width
            if frame[y][x] or (x+1 < W and frame[y][x+1]):
                row += "#"
            else:
                row += "."
        print(row)

# Generate frames
print("// Dog animation frames for 128x32 OLED")
print("// Generated by generate_dog_frames.py")
print()

# Idle frame 1: tail left
frame = new_frame()
draw_dog_base(frame)
draw_tail(frame, 'left')
print("// Idle frame 1 - tail left")
print_frame_preview(frame)
print()
data = frame_to_bytes(frame)
print(bytes_to_c_array(data, "idle_frame1"))
print()

# Idle frame 2: tail center
frame = new_frame()
draw_dog_base(frame)
draw_tail(frame, 'center')
print("// Idle frame 2 - tail center")
print_frame_preview(frame)
print()
data = frame_to_bytes(frame)
print(bytes_to_c_array(data, "idle_frame2"))
print()

# Idle frame 3: tail right
frame = new_frame()
draw_dog_base(frame)
draw_tail(frame, 'right')
print("// Idle frame 3 - tail right")
print_frame_preview(frame)
print()
data = frame_to_bytes(frame)
print(bytes_to_c_array(data, "idle_frame3"))
print()

# Tap frame 1: left paw down
frame = new_frame()
draw_dog_typing_base(frame)
draw_typing_paws(frame, True)
print("// Tap frame 1 - left paw down")
print_frame_preview(frame)
print()
data = frame_to_bytes(frame)
print(bytes_to_c_array(data, "tap_frame1"))
print()

# Tap frame 2: right paw down
frame = new_frame()
draw_dog_typing_base(frame)
draw_typing_paws(frame, False)
print("// Tap frame 2 - right paw down")
print_frame_preview(frame)
print()
data = frame_to_bytes(frame)
print(bytes_to_c_array(data, "tap_frame2"))
