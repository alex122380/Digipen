# ------------------------------------------------------------
# Class:    MAT300 spring 2021
# Project:  Project 2
# Author:   Yi-Chun Chen
# Email:    yichun.chen@digipen.edu
# ------------------------------------------------------------
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys

# ------------------------------------------------------------
# Global variables 
# ------------------------------------------------------------
fig = plt.figure()
fig.canvas.set_window_title('Project 2')
ax = fig.add_subplot(1, 1, 1)

# Control points
d = 1 # Default set to 1
a = [] # control_x in polynomial format
b = [] # control_y in polynomial format
control_x = []
control_y = []

# Methods
method = 0 # 0: NLI, 1: BB-form, 2:Midpoint Subdivision

# For NLI
shells_x = []
shells_y = []
tNLI = 0.5
TOGGLE = True

# For BB-form
pascal = [[1 for i in range(20 + 1)] for j in range(20 + 1)]

# Mouse event
CLICKING = False
RECORDING = True
target = -1

# ------------------------------------------------------------
# Functions 
# ------------------------------------------------------------
def ConfigPlot():
    global fig
    global ax
    
    # Set left y-axis to origin
    ax.spines['left'].set_position(('data', 0.0))
    # Eliminate upper and right axes
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    # Show ticks in the left and lower axes only
    ax.xaxis.set_ticks_position('bottom')
    ax.yaxis.set_ticks_position('left')
    # Set x-axis and y-axis range
    plt.xlim([0, 1])
    plt.ylim([0, 1])
    # Show gray grid lines
    plt.minorticks_on()
    plt.grid(b=True, which='major', color='#999999', linestyle='-', alpha=0.2)
    plt.grid(b=True, which='minor', color='#999999', linestyle='-', alpha=0.2)

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

def PolyValue(x, coeffs):
    d = len(coeffs)
    y = 0
    for i in range(d):
        y += coeffs[i] * x ** i
    return y

def CalculateNextStage(current):
    next = []
    for i, p in enumerate(current[:-1]):
        next.append(PolyAdd(PolyMultiply(p, [1, -1]), PolyMultiply(current[i + 1], [0, 1])))
    return next

def NLI(p, dim, xy):
    global shells_x
    global shells_y
    
    while (dim > 0):
        p = CalculateNextStage(p)
        dim -= 1
        if (xy == 0):
            shells_x.append(p)
        else:
            shells_y.append(p)
    return p

def BBForm(p, dim):
    global pascal
    result = [0 for n in range(dim + 1)]
    for i in range(dim + 1):
        s = p[i][0] * pascal[dim][i]
        
        p1 = [0 for n in range(dim - i + 1)]
        for j in range(dim - i + 1):
            p1[j] = (-1) ** j * pascal[dim - i][j]

        p2 = [0 for n in range(i + 1)]
        p2[i] = 1

        result = PolyAdd(result, PolyScale(PolyMultiply(p1, p2), s))
    return [result]

def MidpointSub(p, dim, k):
    if (k == 0):
        return p
    
    Q = []
    R = []
    Q.append([PolyValue(0.5, p[0])])
    R.insert(0, [PolyValue(0.5, p[-1])])
    for i in range(dim):
        p = CalculateNextStage(p)
        Q.append([PolyValue(0.5, p[0])])
        R.insert(0, [PolyValue(0.5, p[-1])])
        
    return MidpointSub(Q, dim, k - 1) + MidpointSub(R, dim, k - 1)

def Draw():
    global fig
    global ax
    global control_x
    global control_y
    global shells_x
    global shells_y
    global a
    global b
    global RECORDING
    global tNLI

    # Clear screen
    plt.cla()
    ax.clear()
    # Config plot
    ConfigPlot()

    # Update values for plot
    control_x = [] # Reset control points
    control_y = []
    for i in range(len(a)):
        control_x.append(a[i][0])
        control_y.append(b[i][0])
    
    # Plot curve
    if (not RECORDING):
        # Calculate Bezier curve
        if (method == 0):
            # NLI
            shells_x = []
            shells_y = []
            p0 = NLI(a, d, 0) # 0 = x
            p1 = NLI(b, d, 1) # 0 = y
            t = np.linspace(0, 1, num = 500)
            ax.plot(PolyValue(t, p0[0]), PolyValue(t, p1[0]))
            # Plot shells
            if (TOGGLE):
                for i in range(d):
                    temp_x = []
                    temp_y = []
                    for j in range(d - i):
                        temp_x.append(PolyValue(tNLI / 1000, shells_x[i][j]))
                        temp_y.append(PolyValue(tNLI / 1000, shells_y[i][j]))
                    ax.plot(temp_x, temp_y, 'ro-', color='gray')
        elif(method == 1):
            # BB-form
            p0 = BBForm(a, d) # 0 = x
            p1 = BBForm(b, d) # 0 = y
            t = np.linspace(0, 1, num = 500)
            ax.plot(PolyValue(t, p0[0]), PolyValue(t, p1[0]))
        else:
            # Midpoint subdivision
            k = 4 # Approximation times
            MS_x = MidpointSub(a, d, k)
            MS_y = MidpointSub(b, d, k)
            ax.plot(MS_x, MS_y)
            
    # Plot control points
    ax.plot(control_x, control_y,'ro-')
    
    plt.draw()

def CheckTarget(event):
    global target
    min_dis = sys.maxsize 
    for i in range(len(control_x)):
        dis = (event.xdata - control_x[i]) ** 2 + (event.ydata - control_y[i]) ** 2
        if (dis < min_dis):
            target = i
            min_dis = dis

def OnClick(event):
    global d
    global CLICKING
    global RECORDING
    global a
    global b
    global target
    
    CLICKING = True
    if (event.xdata != None and event.ydata != None):
        if (RECORDING):
            a.append([event.xdata])
            b.append([event.ydata])
        else:
            CheckTarget(event)
            a[target][0] = event.xdata
            b[target][0] = event.ydata
    Draw()

def OnRelease(event):
    global CLICKING
    global RECORDING
    CLICKING = False
    if (len(a) >= d + 1):
        RECORDING = False
        Draw()

def OnMove(event):
    global CLICKING
    global RECORDING
    if (CLICKING):
        if (event.xdata != None and event.ydata != None):
            if ((not RECORDING) and (target >= 0)):
                a[target][0] = event.xdata
                b[target][0] = event.ydata
        Draw()

def OnDChange(i):
    global d
    global a
    global b
    global RECORDING
    
    d = i
    a = []
    b = []
    RECORDING = True
    Draw()

def OnTChange(i):
    global tNLI

    tNLI = i
    Draw()

def OnButtonClicked():
    global TOGGLE

    TOGGLE = not TOGGLE
    Draw()

def OnMethodChange(i):
    global method
    method = i
    Draw()

def ConstructPascal():
    global pascal
    for dim in range(20 + 1):
        if (dim >= 2):
            for i in range(dim):
                if (i >= 1):
                    pascal[dim][i] = pascal[dim - 1][i - 1] + pascal[dim - 1][i]

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

# d dropdown menu
dDropDown = QtWidgets.QComboBox(parent=panel)
dDropDown.setToolTip('d')
dDropDown.addItems([ "0",  "1",  "2",  "3",  "4",
                     "5",  "6",  "7",  "8",  "9",
                    "10", "11", "12", "13", "14",
                    "15", "16", "17", "18", "19",
                    "20"])
dDropDown.setCurrentIndex(1)
dDropDown.currentIndexChanged.connect(OnDChange)

# Method dropdown menu
methodDropDown = QtWidgets.QComboBox(parent=panel)
methodDropDown.setToolTip('Method')
methodDropDown.addItems(["NLI", "BB-form", "Midpoint Subdivision"])
methodDropDown.currentIndexChanged.connect(OnMethodChange)

# t toggle button
tButton = QtWidgets.QPushButton('Shells Toggle', parent=panel)
tButton.clicked.connect(OnButtonClicked)

# t slider
tSlider = QtWidgets.QSlider(Qt.Horizontal, parent=panel)
tSlider.setToolTip('t')
tSlider.valueChanged.connect(OnTChange)
tSlider.setRange(0, 1000)
tSlider.setValue(500) # default to 0.5

hbox.addWidget(dDropDown)
hbox.addWidget(methodDropDown)
hbox.addWidget(tButton)
hbox.addWidget(tSlider)
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

ConstructPascal()
Draw()
plt.show()
















