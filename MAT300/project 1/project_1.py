import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# ------------------------------------------------------------
# Global variables 
# ------------------------------------------------------------
fig = plt.figure()
fig.canvas.set_window_title('Project 1')
ax = fig.add_subplot(1, 1, 1)

method = 0 # 0: NLI, 1: BB-form
d = 1 # Default set to 1
a = [[1] for i in range(d + 1)] # d + 1 polynomials
CLICKING = 0
target = 0
control_x = [0 for i in range(d + 1)]
spacing = 1 / (d + 2)
position = spacing
for i in range(d + 1):
    control_x[i] = position
    position += spacing

pascal = [[1 for i in range(20 + 1)] for j in range(20 + 1)]

# ------------------------------------------------------------
# Functions 
# ------------------------------------------------------------
def PolyMultiply(p1, p2):
    result_coeffs = [0] * (len(p1) + len(p2) - 1)
    for index1, coeff1 in enumerate(p1):
        for index2, coeff2 in enumerate(p2):
            result_coeffs[index1 + index2] += coeff1 * coeff2
    return result_coeffs

def PolyAdd(p1, p2):
    return [sum(a) for a in zip(p1, p2)]

def PolyScale(p, s):
    for i in range(len(p)):
        p[i] *= s
    return p

def CalculateNextStage(current):
    next = []
    for i, a in enumerate(current[:-1]):
        next.append(PolyAdd(PolyMultiply(a, [1, -1]), PolyMultiply(current[i + 1], [0, 1])))
    return next

def NLI(a, dim):
    while (dim > 0):
        a = CalculateNextStage(a)
        dim -= 1
    return a

def BBForm():
    global d
    global a
    global pascal
    p = [0 for n in range(d + 1)]
    for i in range(d + 1):
        s = a[i][0] * pascal[d][i]
        
        p1 = [0 for n in range(d - i + 1)]
        for j in range(d - i + 1):
            p1[j] = (-1) ** j * pascal[d - i][j]

        p2 = [0 for n in range(i + 1)]
        p2[i] = 1

        p = PolyAdd(p, PolyScale(PolyMultiply(p1, p2), s))
    return list([p])
        

def PolyValue(x, coeffs):
    d = len(coeffs)
    y = 0
    for i in range(d):
        y += coeffs[i] * x ** i
    return y

def Draw():
    global fig
    global ax
    global d
    global a
    global control_x
    global method
    plt.cla()
    ax.clear()
    
    # Control points coordinates
    control_y = []
    if (method):
        p = BBForm()
    else:
        p = NLI(a, d)
    # Update values for plot
    for i in range(len(a)):
        control_y.append(a[i][0])
    # Move bottim x-axis to centre, left y-axis to origin
    ax.spines['bottom'].set_position('center')
    ax.spines['left'].set_position(('data', 0.0))
    # Eliminate upper and right axes
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    # Show ticks in the left and lower axes only
    ax.xaxis.set_ticks_position('bottom')
    ax.yaxis.set_ticks_position('left')
    # Set x-axis and y-axis range
    plt.xlim([0, 1])
    plt.ylim([-3, 3])
    # Show gray grid lines
    plt.minorticks_on()
    plt.grid(b=True, which='major', color='#999999', linestyle='-', alpha=0.2)
    plt.grid(b=True, which='minor', color='#999999', linestyle='-', alpha=0.2)
    # Plot polynomial
    t = np.linspace(0, 1, num = 500)
    ax.plot(t, PolyValue(t, p[0]))
    # Plot control points
    ax.plot(control_x, control_y,'ro')
    
    plt.draw()

def CheckTarget(event):
    global target
    min_dis = 9999 
    for i in range(len(control_x)):
        dis = abs(event.xdata - control_x[i])
        if (dis < min_dis):
            target = i
            min_dis = dis

def OnClick(event):
    global CLICKING
    CLICKING = 1
    if (event.xdata != None and event.ydata != None):
        CheckTarget(event)
        a[target][0] = event.ydata
    Draw()

def OnRelease(event):
    global CLICKING
    CLICKING = 0

def OnMove(event):
    global CLICKING
    if (CLICKING):
        if (event.xdata != None and event.ydata != None):
            a[target][0] = event.ydata
        Draw()

def OnDChange(i):
    global d
    global a
    global control_x
    d = i
    # Update user options
    a = [[1] for i in range(d + 1)] # d + 1 polynomials
    control_x = [0 for i in range(d + 1)]
    spacing = 1 / (d + 2)
    position = spacing
    for i in range(d + 1):
        control_x[i] = position
        position += spacing
    Draw()

def OnMethodChange(i):
    global method
    method = i
    Draw()

def ConstructPascal():
    global pascal
    for d in range(20 + 1):
        if (d >= 2):
            for i in range(d):
                if (i >= 1):
                    pascal[d][i] = pascal[d - 1][i - 1] + pascal[d - 1][i]
    

# ------------------------------------------------------------
# Control panel 
# ------------------------------------------------------------
# Reference:
# https://stackoverflow.com/questions/28001532/interactive-matplotlib-plots-via-textboxes
#
from PyQt5 import QtGui
from PyQt5 import QtCore
from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt

root = fig.canvas.manager.window
panel = QtWidgets.QWidget()
hbox = QtWidgets.QHBoxLayout(panel)
dDropDown = QtWidgets.QComboBox(parent = panel)
dDropDown.setToolTip('d')
dDropDown.addItems([ "0",  "1",  "2",  "3",  "4",
                     "5",  "6",  "7",  "8",  "9",
                    "10", "11", "12", "13", "14",
                    "15", "16", "17", "18", "19",
                    "20"])
dDropDown.setCurrentIndex(1)
dDropDown.currentIndexChanged.connect(OnDChange)

methodDropDown = QtWidgets.QComboBox(parent = panel)
methodDropDown.setToolTip('Method')
methodDropDown.addItems(["NLI", "BB-form"])
methodDropDown.currentIndexChanged.connect(OnMethodChange)

hbox.addWidget(dDropDown)
hbox.addWidget(methodDropDown)
panel.setLayout(hbox)

dock = QtWidgets.QDockWidget("Options", root)
root.addDockWidget(Qt.TopDockWidgetArea, dock)
dock.setWidget(panel)

# ------------------------------------------------------------
# Main 
# ------------------------------------------------------------

# Register call back functions
cid = fig.canvas.mpl_connect('button_press_event', OnClick)
cid = fig.canvas.mpl_connect('button_release_event', OnRelease)
cid = fig.canvas.mpl_connect('motion_notify_event', OnMove)

# Construct pascal triangle
ConstructPascal()

Draw()
plt.show()














