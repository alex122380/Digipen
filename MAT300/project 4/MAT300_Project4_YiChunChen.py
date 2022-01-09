# ------------------------------------------------------------
# Class:    MAT300 spring 2021
# Project:  Project 4
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
fig.canvas.set_window_title('Project 4')
ax = fig.add_subplot(1, 1, 1)

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

def SplineValue(t, coeffs):
    d = len(coeffs)
    result = []
    for ti in t:
        y = 0
        for i in range(d):
            if i < 4: # Cubic
                y += coeffs[i] * ti ** i
            else: # Truncated power functions
                if ti >= (i - 3):
                    y += coeffs[i] * (ti - (i - 3)) ** 3
        result.append(y)
    return result

def Draw():
    global tx
    global ty
    
    # Clear screen
    plt.cla()
    ax.clear()
    # Config plot
    ConfigPlot()

    # Construct linear system
    L = []
    if len(tx) >= 2:
        for t in range(len(tx) + 2):
            temp = []
            if t < len(tx):
                for i in range(len(tx) + 2):
                    if i < 4:
                        temp.append(t ** i)
                    else: # truncated power functions
                        if t < (i - 3):
                            temp.append(0)
                        else:
                            temp.append((t - (i - 3)) ** 3)
            else: # f''(0) and f''(k)
                for i in range(len(tx) + 2):
                    if i == 0 or i == 1:
                        temp.append(0)
                    elif i == 2:
                        temp.append(2)
                    elif i == 3:
                        if t == len(tx):
                            temp.append(0)
                        elif t == len(tx) + 1:
                            temp.append(6 * (len(tx) - 1))
                    else: # i >= 4
                        if t == len(tx):
                            temp.append(0)
                        elif t == len(tx) + 1:
                            temp.append(6 * ((len(tx) - 1) - (i - 3)))
            L.append(temp)

    # Solve the linear system
    if len(tx) >= 2:
        # Add f''(0) and f''(k) 's value
        temp_tx = tx.copy()
        temp_tx.append(0)
        temp_tx.append(0)
        temp_ty = ty.copy()
        temp_ty.append(0)
        temp_ty.append(0)
        # Solve using linalg.solve()
        X = np.linalg.solve(L, temp_tx)
        Y = np.linalg.solve(L, temp_ty)
        # Plot spline
        para_t = np.linspace(0, len(tx) - 1, num = 500)
        ax.plot(SplineValue(para_t, X), SplineValue(para_t, Y))

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
    if (event.xdata != None and event.ydata != None):
        CheckTarget(event)
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
    global tx
    global ty

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
















