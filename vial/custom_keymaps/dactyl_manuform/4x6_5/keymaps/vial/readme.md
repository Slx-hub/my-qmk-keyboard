# Dactyl Manuform 4x6_5 - Full Split Keyboard Configuration

This is the Vial configuration for the complete split Dactyl Manuform keyboard with 4 rows, 6 columns, and 5 thumb keys per half (50 keys total).

## Hardware Setup

### Wiring
- **Serial Communication**: Connect D0 pin on left half to D0 pin on right half
- **Power**: Connect VCC to VCC and GND to GND between halves
- **Matrix**: Each half uses identical wiring (horizontally mirrored)
  - Columns: D4, C6, D7, E6, B4, B5
  - Rows: F7, B1, B3, B2, B6

### Split Communication
The keyboard uses **serial communication** over pin D0 to sync between halves. This requires only 3 wires (GND, VCC, D0).

## Flashing Instructions

### Important: Each Half Must Be Flashed Separately!

1. **Build the firmware** from vial-qmk directory:
   ```bash
   qmk compile -kb handwired/dactyl_manuform/4x6_5 -km vial
   ```

2. **Flash the LEFT half**:
   - Connect the left half to your computer via USB
   - Put it into bootloader mode (double-tap reset or bridge RST to GND)
   - Flash using QMK Toolbox or command line:
     ```bash
     qmk flash -kb handwired/dactyl_manuform/4x6_5 -km vial
     ```

3. **Flash the RIGHT half**:
   - **Disconnect the left half**
   - Connect the right half to your computer via USB
   - Put it into bootloader mode
   - Flash with the **same firmware file**:
     ```bash
     qmk flash -kb handwired/dactyl_manuform/4x6_5 -km vial
     ```

4. **Connect the halves**:
   - Connect GND, VCC, and D0 between the two halves
   - Plug either half into your computer via USB
   - The keyboard will automatically detect which half is the master

### Master Selection

The keyboard determines which half is "master" based on which one is connected via USB:
- **USB connected to LEFT**: Left half is master
- **USB connected to RIGHT**: Right half is master
bbB*Bt
You can plug USB into either half and it will work correctly!

## Matrix Layout

### Matrix Rows (Total: 10)
- Rows 0-4: Left half (F7, B1, B3, B2, B6)
- Rows 5-9: Right half (F7, B1, B3, B2, B6)

### Matrix Organization
```
Left Half:          Right Half:
Row 0, Cols 0-5     Row 5, Cols 0-5
Row 1, Cols 0-5     Row 6, Cols 0-5
Row 2, Cols 0-5     Row 7, Cols 0-5
Row 3, Cols 1-3     Row 8, Cols 2-4
Row 4, Cols 0-3     Row 9, Cols 2-5
```

## Using Vial GUI

1. Flash both halves as described above
2. Connect either half via USB (both halves connected via serial)
3. Open Vial GUI
4. You will see the **full 50-key layout** displayed
5. You can remap **any key** on either half through the GUI
6. Changes are saved to the keyboard's EEPROM

## Troubleshooting

### Keys on one half don't work
- Check serial connection between halves (D0 to D0, GND to GND, VCC to VCC)
- Verify both halves are flashed with the same firmware
- Check which half is master (connected via USB)

### Vial doesn't show the full layout
- Make sure both halves are connected via serial
- Verify the firmware was built with `SPLIT_KEYBOARD = yes` in rules.mk
- Check that keyboard.json has `"enabled": true` in the split section

### One half is reversed/mirrored
- This is normal! The right half is horizontally mirrored
- Matrix position [5,0] on right half is the leftmost key (index finger position)

## Files in this Configuration

- **config.h**: Vial-specific settings (UID, unlock combo, layer count)
- **rules.mk**: Build options (enables split keyboard and Vial)
- **keymap.c**: Key assignments for all 4 layers
- **vial.json**: GUI layout definition (embedded in firmware)

## Layers

1. **BASE**: Default QWERTY layout
2. **FUNCTION**: Arrow keys, F-keys, navigation
3. **SYMBOL**: Numbers, symbols, media keys
4. **SPECIAL**: Advanced functions, bootloader access

Access layers using the thumb keys defined as `FUNCTION`, `SYMBOL`, etc.
