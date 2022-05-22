import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
# this goes at the top of the Python script
from embedded_window import Window
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import plot_confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
from micromlgen import port

if __name__ == '__main__':
    # assume you saved your recordings into a "data" folder
    stationary = pd.read_csv("stationary.csv")
    #circle = pd.read_csv('circle.csv')
    line = pd.read_csv('line.csv')
    nike = pd.read_csv('tick.csv')
    sqr = pd.read_csv('sqr.csv')


    #stationary.plot(title='stationary')
    #circle.plot(title='circle')
    #square.plot(title='square')
    #triangle.plot(title='triangle')

    #plt.show()

    # X is the array of features to train the model on
    # y is the array of labels
    X = np.vstack([
        stationary.to_numpy(),
       # circle.to_numpy(),
        line.to_numpy(),
        nike.to_numpy(),
        sqr.to_numpy(),
    ])

    y = np.concatenate([
        0 * np.ones(len(stationary)),
       # 1 * np.ones(len(circle)),
        1 * np.ones(len(line)),
        2 * np.ones(len(nike)),
        3 * np.ones(len(sqr)),
    ])

    print("X.shape", X.shape)
    print("y.shape", y.shape)

# the rest goes right after the previous block of code
# if using a board different than Rp2040 Connect, the sampling rate may be different!
SAMPLING_RATE = 104
# this is in milliseconds
WINDOW_DURATION = 500

window = Window(length=SAMPLING_RATE * WINDOW_DURATION // 1000, shift=WINDOW_DURATION // 20)

# X_windows holds the input arranged in windows
# features holds the extracted features for each window (min/max/mean/std...)
# y_windows holds the most frequent label inside each window 
X_windows, features, y_windows = window.fit_transform(X, y)

print('X_windows.shape', X_windows.shape)
print('features.shape', features.shape)
print('y_windows.shape', y_windows.shape)

# use half data for training, half for testing
X_train, X_test, y_train, y_test = train_test_split(features, y_windows, test_size=0.5, random_state=0)
clf = RandomForestClassifier(n_estimators=10, max_depth=10, random_state=0).fit(X_train, y_train)

#plot_confusion_matrix(clf, X_test, y_test, normalize=None, display_labels=['stationary', 'circle', 'shaking'])

ConfusionMatrixDisplay.from_estimator(clf, X_test, y_test, normalize=None, display_labels=['stationary','line','nike', 'square'])
plt.show()

with open("Window.h", "w") as file:
    file.write(window.port())

with open("Classifier.h", "w") as file:
    file.write(port(clf, classname="Classifier", classmap={0: "stationary", 1: "line", 2: "nike", 3: "square"}))