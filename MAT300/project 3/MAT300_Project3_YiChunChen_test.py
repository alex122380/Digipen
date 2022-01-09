# ------------------------------------------------------------
# Class:    MAT300 spring 2021
# Project:  Project 3
# Author:   Yi-Chun Chen
# Email:    yichun.chen@digipen.edu
# ------------------------------------------------------------
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys
from itertools import zip_longest

# ------------------------------------------------------------
# Global variables 
# ------------------------------------------------------------
fig = plt.figure()
fig.canvas.set_window_title('Project 3')
ax = fig.add_subplot(1, 1, 1)

gx = []
gy = []
tx = []
ty = []

# Mouse event
target = -1
CLICKING = False

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
    plt.xlim([0, 10])
    plt.ylim([0, 10])
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
    return [a + b for a, b in zip_longest(p1, p2, fillvalue=0)]

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

def NewtonFrom(g):
    p = []
    for i in range(len(g)):
        temp = [1]
        for j in range(i):
            temp = PolyMultiply(temp, [-j, 1])
        p = PolyAdd(p, PolyScale(temp, g[i][0]))
    return p

def Draw():
    global tx
    global ty
    global gx
    global gy
    
    # Clear screen
    plt.cla()
    ax.clear()
    # Config plot
    ConfigPlot()

    # Calculate divided difference table
    # Reset
    gx = []
    gy = []
    # Stage 0
    if len(tx) > 0:
        gx.append(tx)
        gy.append(ty)
    # Other stages
    for i in range(len(tx) - 1):
        temp_x = []
        temp_y = []
        for j in range(len(gx[i]) - 1):
            temp_x.append((gx[i][j+1] - gx[i][j]) / (i+1+j - j))
            temp_y.append((gy[i][j+1] - gy[i][j]) / (i+1+j - j))
        gx.append(temp_x)
        gy.append(temp_y)
    
    # Calculate the polynomial using newton form
    px = NewtonFrom(gx)
    py = NewtonFrom(gy)

    t = np.linspace(0, len(px) - 1, num = 500)
    ax.plot(PolyValue(t, px), PolyValue(t, py))

    # Plot interpolation points
    ax.plot(tx, ty,'ro')
    
    plt.draw()

def CheckTarget(event):
    global target
    min_dis = sys.maxsize 
    for i in range(len(tx)):
        dis = (event.xdata - tx[i]) ** 2 + (event.ydata - ty[i]) ** 2
        if (dis < min_dis):
            target = i
            min_dis = dis
    if min_dis > 0.05:
        target = -1

def OnClick(event):
    global tx
    global ty
    global target
    global CLICKING

    CLICKING = True
    CheckTarget(event)
    if (event.xdata != None and event.ydata != None):
        if target == -1:
            tx.append(event.xdata)
            ty.append(event.ydata)
        else:
            tx[target] = event.xdata
            ty[target] = event.ydata
    Draw()

def OnRelease(event):
    global CLICKING

    CLICKING = False

def OnMove(event):
    global CLICKING

    if CLICKING:
        if (event.xdata != None and event.ydata != None):
            if target != -1:
                tx[target] = event.xdata
                ty[target] = event.ydata
                Draw()

def OnButtonClicked():
    global gx
    global gy
    global tx
    global ty
    
    gx = []
    gy = []
    tx = []
    ty = []
    Draw()
    
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

# Reset button
tButton = QtWidgets.QPushButton('Reset', parent=panel)
tButton.clicked.connect(OnButtonClicked)

hbox.addWidget(tButton)
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

Draw()
plt.show()
















