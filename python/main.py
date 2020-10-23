import pygame
from pygame.locals import *
from random import randint

SIZE = (700, 700)

def setup():
	pygame.init()
	window = pygame.display.set_mode(SIZE)
	window.fill((0,0,0))
	return SIZE[0], SIZE[1], window

def initial_fill(width, height, window):
	#pixels = pygame.PixelArray(pygame.Surface(SIZE))
	pixels = [[randint(0,10) for i in range(height)] for j in range(width)]
	for i in range(width):
		for j in range(height):
			#pixels[i][j] = randint(0,1)
			if pixels[i][j]:
				pygame.draw.rect(window, (255, 0, 0), (i, j, 1, 1))
	return pixels

def valid_indices(i, width, height):
	return (0 < i[0] < width) and (0 < i[1] < height)

def get_neighbors(i, j, pixels, width, height):
	active_neighbors = 0
	indices = lambda x,y: ((x-1,y-1),(x,y-1),(x+1,y-1),(x-1,y),(x+1,y),(x-1,y+1),(x,y+1),(x+1,y+1))
	ix = indices(i,j)
	for idx, i in enumerate(ix):
		if valid_indices(i, width, height):
			if pixels[i[0]][i[1]]:
				active_neighbors += 1
	return active_neighbors

def compute_next_gen(width, height, pixels, window, new_color):
	for i in range(width):
		for j in range(height):
			neighbors = get_neighbors(i, j, pixels, width, height)
			if (neighbors < 2 or neighbors > 3) and pixels[i][j]:
				# death from overpopulation
				pixels[i][j] = 0
				pygame.draw.rect(window, (0, 0, 0), (i, j, 1, 1))
			elif (1 < neighbors < 4) and pixels[i][j]:
				# lives on to next generation
				continue
			elif (neighbors == 3) and not pixels[i][j]:
				# birth of new cells
				pixels[i][j] = 1
				pygame.draw.rect(window, new_color, (i, j, 1, 1))
	return pixels

def main():

	width, height, window = setup()

	pixels = initial_fill(width, height, window)

	while True:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				quit()

		# compute next generation
		new_color = (randint(0,255), randint(0,255), randint(0,255))
		pixels = compute_next_gen(width, height, pixels, window, new_color)
		#print(pixels)
		#window.blit(pixels.make_surface(), (0,0))
		pygame.display.update()

main()
