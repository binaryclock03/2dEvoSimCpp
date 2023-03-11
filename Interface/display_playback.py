import time
import pygame as pg
import os

def play():
    path_to = os.path.join(os.path.dirname(__file__), "Playback")
    files = os.listdir(path_to)
    with open(os.path.join(path_to, files[0])) as f:
        gridsize = (128,128) 
        reader = f.readline()

        pg.init()
        display = pg.display.set_mode((800,800))
        pg.display.set_caption("Creatures Playback Display")

        time1 = time.time()
        time2 = time.time()
        while True:
            if (time2 - time1) > 0.1:
                time1 = time.time()
                reader = f.readline()
            
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    pg.quit()
                    return False
                if event.type == pg.KEYDOWN:
                    keydown = pg.key.get_pressed()
                    if keydown[pg.K_1]:
                        pass

            display.fill((255,255,255))

            creatures = reader.split(",")
            del creatures[-1]

            for i in creatures:
                x = int(i) % gridsize[0]
                y = (int(i) - x)/gridsize[1]

                color = (0,0,0)
                pg.draw.circle(display, color, (x*6+16,y*6+16), 3)
            
            time2 = time.time()

            pg.display.update()

if __name__ == "__main__" and True:
    play()
