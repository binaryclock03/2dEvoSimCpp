import time
import pygame as pg
import os

def play():
    path_to = os.path.join(os.path.dirname(__file__), "Playback")
    files = os.listdir(path_to)
    with open(os.path.join(path_to, files[0])) as f:
        reader = f.readline()

        gridsize = (128,128) 
        reader = f.readline()

        pg.init()
        display = pg.display.set_mode((928,928))
        pg.display.set_caption("Creatures Playback Display")

        time1 = time.time()
        time2 = time.time()

        paused = True

        while True:
            if (time2 - time1) > 0.1 and not paused:
                time1 = time.time()
                reader = f.readline()
            
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    pg.quit()
                    return False
                if event.type == pg.KEYDOWN:
                    keydown = pg.key.get_pressed()
                    if keydown[pg.K_SPACE]:
                        paused = not paused

            display.fill((255,255,255))
            pg.draw.rect(display, (200,200,200), pg.Rect(16-4,16-4,928-32+4,928-32+8))

            creatures = reader.split(",")
            del creatures[-1]

            for i in creatures:
                id = int(i.split(":")[0])
                pos = int(i.split(":")[1])
                
                if pos != -1:
                    x = pos % gridsize[0]
                    y = (pos - x)/gridsize[1]

                    if id == 49: color = (255,0,0)
                    else: color = (0,0,0)

                    pg.draw.circle(display, color, (x*7+16,y*7+16), 4)
            
            time2 = time.time()

            pg.display.update()

if __name__ == "__main__" and True:
    play()
