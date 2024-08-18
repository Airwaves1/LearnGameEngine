# Description: This file is used to install the required packages for the project.
# Author: Airwave
# Last Modified: 2024-08-18

# 1. 安装必要的工具包，通过系统包管理工具安装
# Windows: Winget， Linux：apt-get， MacOS: brew
# Python, Windows: winget install python, Linux: apt-get install python, MacOS: brew install python 
# CMake,  Windows: winget install cmake, Linux: apt-get install cmake, MacOS: brew install cmake
# git,  Windows: winget install git, Linux: apt-get install git, MacOS: brew install git
# vulkan， Windows: winget install vulkan, Linux: apt-get install vulkan, MacOS: brew install vulkan


import os
import subprocess
import pkg_resources

# 获取当前系统
def get_current_system():
    if os.name == 'nt':
        return 'Windows'
    elif os.name == 'posix':
        return 'Linux'
    elif os.name == 'mac':
        return 'MacOS'
    else:
        return 'Other'

# 检查必要工具是否安装, 如果没有将自动调用系统包管理工具安装
def check_tools():
    if get_current_system() == 'Windows':
        try:
            pkg_resources.get_distribution('python')
        except pkg_resources.DistributionNotFound:
            print('Python is not installed, please run "winget install python" to install it.')
            exit(1)
        try:
            pkg_resources.get_distribution('cmake')
        except pkg_resources.DistributionNotFound:
            print('CMake is not installed, please run "winget install cmake" to install it.')
            exit(1)
        try:
            pkg_resources.get_distribution('git')
        except pkg_resources.DistributionNotFound:
            print('Git is not installed, please run "winget install git" to install it.')
            exit(1)
        try:
            pkg_resources.get_distribution('vulkan')
        except pkg_resources.DistributionNotFound:
            print('Vulkan is not installed, please run "winget install vulkan" to install it.')
            exit(1)