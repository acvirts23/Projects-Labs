#Tristan Kieffer and Andrew Virts
​
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import np_utils
from sklearn.preprocessing import LabelEncoder, MinMaxScaler
from numpy import loadtxt
​
#import data and set to x and y
dataset = loadtxt('wine_train.csv', delimiter=",")
x = dataset[:,1:14]
y = dataset[:,0]
​
#encode class values as integers
encoder = LabelEncoder()
encoder.fit(y)
encoded_Y = encoder.transform(y)
# convert integers to dummy variables (i.e. one hot encoded)
dummy_y = np_utils.to_categorical(encoded_Y)
​
# define baseline model
def get_model():
​
    #create model for our network
    model = Sequential()

    #Adds the first hidden layer with 10 nodes and can take in 13 variables
    model.add(Dense(10, input_dim=13, activation='relu'))
    #second hidden layer
    #Adding more layers would be inefficient and would most likely not increase performance at this point
    #Adding more layers could potentially lead to overfitting
    model.add(Dense(8, activation='relu'))
    #softmax output
    model.add(Dense(3, activation='softmax'))
    
​
    # Compile model
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
    #need scaled to scale the data, helps keep accuracy much higher by putting values closer 
    #to each other so the weights don't get crazy
    scaler = MinMaxScaler()
    scaleVal = scaler.fit_transform(x)
    model.fit(scaleVal, dummy_y, epochs=150, batch_size=10)
    return model
​
​
get_model()