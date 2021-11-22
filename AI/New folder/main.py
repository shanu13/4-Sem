import numpy as np


# FITNESS CALCULATING FUNCTION FOR CALUCULATING THE FITNEDSS OF THE POPULATION
# STATE REPRESENTATION - REAL VALUED ENCODING
def calc_fitness(x):
    if 0 < x <= 6:
        y = 2 * x * x + 1
        return round(y, 6)
    else:
        return 0


fitness = np.vectorize(calc_fitness)


# MUTATION FUNCTION
def mutate(parents, fitness_function):
    n = int(len(parents))  # defining population size
    scores = fitness_function(parents)
    idx = scores > 0
    scores = scores[idx]
    parents = np.array(parents)[idx]
    # resampling the parents with probabilities proportional to their fitness
    children = np.random.choice(parents, size=n, p=scores / scores.sum())
    children = children + np.random.uniform(0, 6, size=n) #adding noise for mutation
    return children.tolist()  # converting array to a list


def GA(parents, fitness_function, population_size=10):
    History = []  # initial parents
    best_parent, best_fitness = get_fittest_parent(parents, fitness)  # getting the best parent with the best fitness
    print('Genenration - 0 ,best fitness - ', best_fitness, ',current fitness - ', best_fitness, ',current parent - ',
          best_parent)
    for i in range(1, 6):
        parents = mutate(parents, fitness_function)
        curr_parent, curr_fitness = get_fittest_parent(parents, fitness_function)  # getting fittest parent
        if curr_fitness > best_fitness:
            best_fitness = curr_fitness
            best_parent = curr_parent
        curr_parent, curr_fitness = get_fittest_parent(parents, fitness_function)
        print('Genenration -', i, ',best fitness - ', best_fitness, ',current fitness - ', curr_fitness,
              ',current parent - ', curr_parent)
        History.append((i, np.max(fitness_function(parents))))
    print('Genenration -', i, ',best fitness - ', best_fitness, ',best parent - ', best_parent)
    return best_parent, best_fitness, History


def get_fittest_parent(parents, fitness):
    calc_fitness = fitness(parents)
    pfitness = list(zip(parents, calc_fitness)) #creating a pair using zip
    pfitness.sort(key=lambda x: x[1], reverse=True)
    best_parent, best_fitness = pfitness[0]
    return round(best_parent, 4), round(best_fitness, 4)


init_pop = np.random.uniform(low=0, high=6, size=20)

parent, fit, history = GA(init_pop, fitness)
print('top_parent - ', parent, ', top fitness - ', fit)
