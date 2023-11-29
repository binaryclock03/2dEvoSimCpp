from math import sqrt
import random
from matplotlib.pyplot import show
import pygame as pg
import lib.netObjects as nt
import lib.genome as g
import lib.functions as f
import lib.util as util

def show_brain(brain):
    pg.init()
    display = pg.display.set_mode((1800,800))
    pg.display.set_caption("Net Display")

    num_sensors = 0
    num_inters = 0
    num_actions = 0
    neurons = {}

    for key in brain.neurons.keys():
        if key <128:
            num_sensors += 1
        elif key <256:
            num_inters += 1
        else:
            num_actions += 1
    
    num1 = 0
    num2 = 0
    for key in list(brain.neurons.keys()):
        if key < 128:
            x = int((((1800-100)/(num_sensors-1)) * (num1)) + 50)
            y = 200
            neurons.update({key:(x,y)})
            num1 += 1
        elif key < 256:
            x = random.randrange(10,1790)
            y = random.randrange(200,400)
            neurons.update({key:(x,y)})
        else:
            x = int((((1800-100)/(num_actions-1)) * (num2)) + 50)
            y = 600
            neurons.update({int(key):(x,y)})
            num2 += 1

    conn = []
    for index in range(256):
        color = (random.randrange(0,255),random.randrange(0,255),random.randrange(0,255))
        conn.append(color)
    
    font = pg.font.Font('freesansbold.ttf', 12)

    while True:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                pg.quit()
                return False
            if event.type == pg.KEYDOWN:
                keydown = pg.key.get_pressed()
                if keydown[pg.K_1]:
                    pass
                    # inter = {}
                    # for index in range(numInters):
                    #     x = random.randrange(10,1790)
                    #     y = random.randrange(300,500)
                    #     inter.update({index+128:(x,y)})
                if keydown[pg.K_2]:
                    conn = []
                    for index in range(256):
                        color = (random.randrange(0,255),random.randrange(0,255),random.randrange(0,255))
                        conn.append(color)

        display.fill((255,255,255))

        i = 0
        for connection in brain.connections:
            adr_a = connection.adr_a
            adr_b = connection.adr_b
                
            if adr_b < 128:
                adr_b += 256

            xb, yb = neurons[adr_b]
            xa, ya = neurons[adr_a]

            color = conn[i]
            pg.draw.line(display, color, (xa,ya), (xb,yb), width=5)
            dx = xb-xa
            dy = yb-ya
            length = sqrt(dx**2 + dy**2)
            if length != 0:
                dx = dx/length
                dy = dy/length
                arrowPos = 0.6
                arrowWidth = 10
                arrowLength = 15
                pg.draw.polygon(display, color, [(xa+dx*length*arrowPos+dx*arrowLength,ya+dy*length*arrowPos+dy*arrowLength), (xa+dx*length*arrowPos+dy*arrowWidth,ya+dy*length*arrowPos+dx*-arrowWidth), (xa+dx*length*arrowPos+dy*-arrowWidth,ya+dy*length*arrowPos+dx*arrowWidth)])
                text = font.render(str(round(connection.strength,2)), True, (0,0,0))
                text_rect = text.get_rect()
                text_rect.center = (xa+dx*length*arrowPos+dx*arrowLength,ya+dy*length*arrowPos+dy*arrowLength)
                display.blit(text, text_rect)
            else:
                pg.draw.circle(display, color, (xa+7,ya-7), 12, width=4)
            i += 1

        for key in neurons.keys():
            coords = neurons[key]

            if key in f.neuron_name_dict.keys():
                text = font.render(f.neuron_name_dict[key], True, (0,0,0))
            else:
                text = font.render(str(key), True, (255,255,255))
            text_rect = text.get_rect()
            text_rect.center = coords

            pg.draw.circle(display, (255,0,255), coords, 12)
            display.blit(text, text_rect)
        
        pg.display.update()

def retrive_gene_from_file(filepath):
    population_n = 1000
    gene_n = 16

    generations = list()

    with open(filepath, "rb") as f:
        for genome_i in range(population_n):
            genomes = list()
            for i in range(gene_n):
                genome = f.read(4).hex()
            if len(genome) == 0:
                break
            genomes[i] = genome

        

if __name__ == "__main__" and True:
    retrive_gene_from_file("../Populations/UHRZ_p1000g16.bin")

    genes_string = "8203bc24 8283db7a 0202abff 06017943 8180b8c6 8104a84a 010429e0 0505a04b 808176e6 05026c22 8201cf0a 0080e4f7 8080a8c5 0602b8ef 050327e7 84048e37"
    re = g.Genome(16,genes=genes_string.split(" "))
    brain = nt.NeuralNet()
    brain.build_net(re)
    brain.optimize()
    show_brain(brain)