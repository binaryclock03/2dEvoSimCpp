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
        display = pg.display.set_mode((128*6+32,128*6+32))
        pg.display.set_caption("Creatures Playback Display")

        time1 = time.time()
        time2 = time.time()

        paused = True
        selected_id = -1
        pos_id = {}

        creature_size = 6
        sim_ue = 16 - (creature_size/2)
        sim_width = (creature_size * gridsize[0])
        sim_height = (creature_size * gridsize[1])

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
                
                if event.type == pg.MOUSEBUTTONDOWN:
                    if pg.mouse.get_pressed()[0]:
                        pos_v = pg.mouse.get_pos()
                        pos_v = (int((pos_v[0] - sim_ue)/6), int((pos_v[1] - sim_ue)/6))

                        pos = pos_v[0] + pos_v[1]*128
                        selected_id = pos_id.get(pos)


            display.fill((255,255,255))

            #draw sim zone and safe zones
            pg.draw.rect(display, (200,200,200), pg.Rect(sim_ue, sim_ue, sim_width, sim_height))
            pg.draw.rect(display, (0,200,100), pg.Rect(sim_ue, sim_ue, sim_width * 1/8, sim_width * 1/8))
            pg.draw.rect(display, (0,200,100), pg.Rect(sim_ue + sim_width * 7/8, sim_ue + sim_width * 7/8, sim_width * 1/8, sim_width * 1/8))
            pg.draw.rect(display, (0,200,100), pg.Rect(sim_ue, sim_ue + sim_width * 7/8, sim_width * 1/8, sim_width * 1/8))
            pg.draw.rect(display, (0,200,100), pg.Rect(sim_ue + sim_width * 7/8, sim_ue, sim_width * 1/8, sim_width * 1/8))

            creatures = reader.split(",")
            del creatures[-1]
            pos_id.clear()

            for i in creatures:
                id = int(i.split(":")[0])
                pos = int(i.split(":")[1])

                pos_id.update({pos: id})

                if pos != -1:
                    x = pos % gridsize[0]
                    y = (pos - x)/gridsize[0]

                    if id == selected_id: color = (255,0,0)
                    else: color = (0,0,0)

                    #pg.draw.rect(display, (0,0,0), pg.Rect(sim_ue + x*6, sim_ue + y*6, 6, 6))
                    pg.draw.circle(display, color, (x*6+16,y*6+16), 3)
            
            time2 = time.time()

            pg.display.update()

if __name__ == "__main__" and True:
    play()
