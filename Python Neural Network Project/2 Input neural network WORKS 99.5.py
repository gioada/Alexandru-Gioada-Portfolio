from matplotlib import pyplot as plt
import numpy

#OVER OR UNDER Y = 5
#TAKES 2 INPUTS X AND Y AND CHECKS WETHER
#THE COORDINATES ARE ABOVE OR BELOW Y = 5
#IT WILL MAKE SENSE IF YOU SKETCH IT ON PAPER

#-0.05080506444578311 2.814888040908459 -15.162886477881228
#99.5%

data=[[0,0,0],[0,1,0],[0,2,0],[0,3,0],[0,4,0],[0,5,0],[0,6,1],[0,7,1],[0,8,1],[0,9,1],[0,10,1],
      [1,0,0],[2,0,0],[3,0,0],[4,0,0],[5,0,0],[6,0,0],[7,0,0],[8,0,0],[9,0,0],[10,0,0],
      [1,1,0],[2,2,0],[3,3,0],[4,4,0],[5,5,0],[6,6,1],[7,7,1],[8,8,1],[9,9,1],[10,10,1],
      [1,2,0],[2,3,0],[3,4,0],[4,5,0],[5,6,1],[6,1,0],[7,2,0],[8,3,0],[9,4,0],[10,5,0],
      [6,1,0],[8,2,0],[9,3,0],[10,4,0],[9,5,0],[8,6,1],[7,5,0],[6,6,1],[5,8,1]]


data2 = [[0,0,0]]
data3 = [[0,0,0]]




#LAYER1
#Trained data. If untrained, these would be random
w1 = -0.05080506444578311
w2 = 2.814888040908459
b =  -15.162886477881228


def CreateData(max,length):
    for i in range(length):
        a = numpy.random.randint(max)
        b = numpy.random.randint(max)
        c = 0
        if b > 5:
            c = 1
        d = [a,b,c]
        data2.append(d)
        
def CreateData2(min,max,length):
    for i in range(length):
        a = numpy.random.randint(min,max)
        b = numpy.random.randint(min,max)
        c = 0
        if b > 5:
            c = 1
        d = [a,b,c]
        data3.append(d)


def Sigmoid(x):
    return 1/(1+numpy.exp(-x))

def SigmoidDer(x):
    return Sigmoid(x)* (1-Sigmoid(x))


def Plot(x,y):
    plt.plot(x,y)
   
    plt.title("Cost w time")
    plt.xlabel("Time")
    plt.ylabel("Cost") 
    plt.show()
    
    
def TestData(x):
    correctcount = 0
    totalcount = len(x)
    for i in range(len(x)):
        i1 = x[i][0]
        i2 = x[i][1]
        ans = numpy.round(NN(i1,i2))
        if ans == x[i][2]:
            correctcount+=1
    print(str(correctcount) + " out of " + str(totalcount) + " were correct")    
    print(str(correctcount/totalcount*100) + " % Correct" )    


learning_rate = 0.0005
y = [0]
y2 = [0]
y3 = [0]
time = [0]
CreateData(10,3000)
CreateData2(-1000,1000,100000)

def TrainNetwork():

    for i in range(5000000):
        

        ri = numpy.random.randint(len(data2))
        point = data2[ri]

        z = (point[0] *w1) + (point[1] *w2) + b

        
        

        prediction = Sigmoid(z)

        
        target = point[2]

        cost = numpy.square(prediction-target)


        #back prop

        dc_dpred = 2*(prediction-target)



        dpred_dz = SigmoidDer(z)


        if i% 1000000 == 0:
                print(i)
                time.append(i)
                y.append(cost)
      
              

        dz_dw1 = point[0]
        dz_dw2 = point[1]
        dz_db = 1

        
        dc_dz = dpred_dz * dc_dpred
        dc_dw1 = dc_dz * dz_dw1
        dc_dw2 = dc_dz * dz_dw2
        dc_db = dc_dz * dz_db
        
        


        w1 = w1 - learning_rate * dc_dw1
        w2 = w2 - learning_rate * dc_dw2
        b = b- learning_rate*dc_db

   
   
    

def NN(x,y):
    z = x *w1 + y *w2 + b
    
    return Sigmoid(z)


print(NN(2,5))
TestData(data)
TestData(data2)
TestData(data3)
Plot(time,y)
print(w1,w2,b)



