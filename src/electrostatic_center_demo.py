from electrostatic_center import electrostatic_center_2d, electrostatic_center_3d

print('2D electrostatic center (x, y) =', electrostatic_center_2d(((-1, 0), (2, 0), (0, 2))))
print('3D electrostatic center (x, y, z) =', electrostatic_center_3d(((-1, 0, 1), (2, 0, 2), (0, 2, 3))))
