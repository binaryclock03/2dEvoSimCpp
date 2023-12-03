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

def show_brain_surface(brain):
    display = pg.Surface((800,800))
    display.fill((255,255,255))

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
            x = int((((800-50)/(num_sensors-1)) * (num1)+25))
            y = 50
            neurons.update({key:(x,y)})
            num1 += 1
        elif key < 256:
            x = random.randrange(50,750)
            y = random.randrange(100,250)
            neurons.update({key:(x,y)})
        else:
            x = int((((800-50)/(num_actions-1)) * (num2)+25))
            y = 300
            neurons.update({int(key):(x,y)})
            num2 += 1

    conn = []
    for index in range(256):
        color = (random.randrange(0,255),random.randrange(0,255),random.randrange(0,255))
        conn.append(color)
    
    font = pg.font.Font('freesansbold.ttf', 12)

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
    
    return display

def retrive_all_genes_from_file(filepath):
    population_n = 1000
    gene_n = 16

    generations = list()
    gen_number = 0
    with open(filepath, "rb") as f:
        while True:
            genomes = list()
            for genome_i in range(population_n):
                genome = str()
                for i in range(gene_n):
                    genome += f.read(4).hex()
                genomes.append(genome)
            generations.append(genomes)

            # check if end of file
            check = f.read(1)
            if (check == b''):
                break
            else: f.seek(f.tell()-1)

            gen_number += 1

    print(f"Number of generations: {len(generations)}")
    print(f"Population: {len(generations[0])}")
    return generations

def retrive_genome_from_file(filepath:str, generation_number:int, creature_id:int):
    population_n = 1000
    gene_n = 16
    bytes_per_gene = 4

    with open(filepath, "rb") as f:
        bytes_per_genome = bytes_per_gene * gene_n
        bytes_per_generation = bytes_per_genome * population_n

        gene_loc = (creature_id * bytes_per_genome) + (generation_number * bytes_per_generation)
        f.seek(gene_loc)

        return f.read(bytes_per_genome).hex()

def show_brain_from_id(filepath, gen_number, creature_id):
    ## Get genome from file
    genes_string = retrive_genome_from_file(filepath, gen_number, creature_id)
    #print(genes_string)

    ## Add spaces so the visualizer can work
    result = ""
    for i in range(0, len(genes_string), 8):
        result += genes_string[i:i+8] + " "
    result = result.strip()
    genes_string = result

    ## Visualize the genome
    #genes_string = "8203bc24 8283db7a 0202abff 06017943 8180b8c6 8104a84a 010429e0 0505a04b 808176e6 05026c22 8201cf0a 0080e4f7 8080a8c5 0602b8ef 050327e7 84048e37"
    re = g.Genome(16,genes=genes_string.split(" "))
    brain = nt.NeuralNet()
    brain.build_net(re)
    brain.optimize()
    return show_brain_surface(brain)

if __name__ == "__main__" and True:
    show_brain_from_id("../Populations/GJDY_p1000g16.bin", 29, 1)