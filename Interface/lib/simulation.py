import lib.netObjects as nt
import random as rand
import lib.util as util

class Simulation():
    def __init__(self):
        self.grid_bounds = (128, 128)
        self.grid = {}
        self.creatures:list = []
        self.tick = 0
    
    def add_to_sim(self, creature):
        creature.simulation = self
        while True:
            x = rand.randrange(0, self.grid_bounds[0])
            y = rand.randrange(0, self.grid_bounds[1])
            if not((x,y) in self.grid.items()):
                break
        self.grid.update({creature.id: (x,y)})
        self.creatures.append(creature)

    def get_creature_position(self, id):
        return self.grid[id]
        print(f"creature with id:{id} not found")

    def move_creature(self, id, dx, dy):
        x, y = self.get_creature_position(id)
        x = util.clamp(x+dx, 0, self.grid_bounds[0])
        y = util.clamp(y+dy, 0, self.grid_bounds[1])
        if not((x,y) in self.grid.items()):
            self.grid.update({id: (x,y)})
            return [dx,dy]
        else:
            print("creature collided")
            return [0,0]

    def simulate(self):
        for creature in self.creatures:
            creature.simulate()
        self.tick += 1

class Creature():
    def __init__(self, id):
        self.id = id
        self.brain = None
        self.genome = None
        self.simulation = None
        self.dir = [rand.randint(-1,1),rand.randint(-1,1)]
        self.delta = [0,0]

    def simulate(self):
        self.brain.activate(self, self.simulation)
        pass

    def build_from_genome(self, genome):
        self.genome = genome
        self.brain = nt.NeuralNet()
        self.brain.build_net(self.genome)
        pass

    def add_io_neurons(self, sensor_neurons, action_neurons):
        for i, neuron in enumerate(sensor_neurons):
            self.brain.insert_neuron(i, neuron)
        
        for i, neuron in enumerate(action_neurons):
            self.brain.insert_neuron(i+256, neuron)
    
    def finalize(self):
        self.brain.optimize()