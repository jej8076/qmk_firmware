#!/usr/bin/env python3
"""Generate keycap animation frames for 128x32 SSD1306 OLED."""

W, H = 128, 32

def new_frame():
    return [[0]*W for _ in range(H)]

def px(frame, x, y, v=1):
    if 0 <= x < W and 0 <= y < H:
        frame[y][x] = v

def fill(frame, x1, y1, x2, y2):
    for y in range(max(0, y1), min(H, y2+1)):
        for x in range(max(0, x1), min(W, x2+1)):
            px(frame, x, y)

def clear(frame, x1, y1, x2, y2):
    for y in range(max(0, y1), min(H, y2+1)):
        for x in range(max(0, x1), min(W, x2+1)):
            px(frame, x, y, 0)

def keycap(frame, dy):
    cx = 64
    # Top face (narrower, with dish/concave inset)
    tw = 17  # half-width = 34px total
    ty = 1 + dy
    tb = ty + 9

    # Front face (wider for 3D perspective)
    fw = 21  # half-width = 42px total
    fy = tb + 1
    fb = 25

    # Top surface
    fill(frame, cx-tw, ty, cx+tw, tb)
    # Round corners
    px(frame, cx-tw, ty, 0); px(frame, cx+tw, ty, 0)
    px(frame, cx-tw, tb, 0); px(frame, cx+tw, tb, 0)
    # Dish inset (clear center for concave look)
    clear(frame, cx-tw+2, ty+2, cx+tw-2, tb-2)

    # Front face
    if fy <= fb:
        fill(frame, cx-fw, fy, cx+fw, fb)
        px(frame, cx-fw, fb, 0); px(frame, cx+fw, fb, 0)
        # Horizontal detail line in middle of front face
        mid = (fy + fb) // 2
        if fb - fy > 4:
            clear(frame, cx-fw+2, mid, cx+fw-2, mid)

    # Base plate
    fill(frame, cx-28, 28, cx+28, 29)

def to_bytes(frame):
    r = []
    for p in range(4):
        for c in range(W):
            b = 0
            for bit in range(8):
                if frame[p*8+bit][c]:
                    b |= 1 << bit
            r.append(b)
    return r

def to_c(data, name):
    lines = [f"static const char PROGMEM {name}[] = {{"]
    for i in range(0, len(data), 16):
        chunk = data[i:i+16]
        s = ", ".join(f"0x{b:02x}" for b in chunk)
        if i + 16 < len(data):
            s += ","
        lines.append(f"    {s}")
    lines.append("};")
    return "\n".join(lines)

def preview(frame):
    for y in range(H):
        r = ""
        for x in range(0, W, 2):
            r += "#" if (frame[y][x] or (x+1 < W and frame[y][x+1])) else "."
        print(r)

# Generate frames
for name, dy in [("idle_frame", 0), ("tap_frame1", 6), ("tap_frame2", 0)]:
    f = new_frame()
    keycap(f, dy)
    print(f"=== {name} (dy={dy}) ===")
    preview(f)
    print()
    print(to_c(to_bytes(f), name))
    print()
