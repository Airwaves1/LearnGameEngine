import os
import re

def is_blank_or_comment(line, file_extension):
    line = line.strip()
    if not line:
        return True
    
    if file_extension in ['.cpp', '.h', '.c']:
        # C++ 注释: 处理单行注释和多行注释
        if line.startswith('//') or re.match(r'^\s*/\*.*\*/\s*$', line):
            return True
        if '/*' in line and '*/' in line:
            return True
        if '/*' in line:
            return True
        if '*/' in line:
            return True
    
    if file_extension == '.py':
        # Python 注释: 处理单行注释
        if line.startswith('#'):
            return True
    
    return False

def count_lines_of_code(root_dir):
    total_lines = 0
    for subdir, _, files in os.walk(root_dir):
        for file in files:
            file_path = os.path.join(subdir, file)
            if file.endswith(('.cpp', '.h', '.c', '.py')):  # 文件类型
                file_extension = os.path.splitext(file)[1]
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    for line in f:
                        if not is_blank_or_comment(line, file_extension):
                            total_lines += 1
    return total_lines

engine_core_directory = './Engine/Core'
engine_platform_directory = './Engine/Platform'
sandbox_directory = './Sandbox'
engine_thirdparty_directory = './Engine/ThirdParty'

engine_core_lines = count_lines_of_code(engine_core_directory)
engine_platform_lines = count_lines_of_code(engine_platform_directory)
engine_thirdparty_lines = count_lines_of_code(engine_thirdparty_directory)
sandbox_lines = count_lines_of_code(sandbox_directory)

print(f'Engine Core: {engine_core_lines} lines')
print(f'Engine Platform: {engine_platform_lines} lines')
print(f'Sandbox: {sandbox_lines} lines')
print(f'Engine ThirdParty: {engine_thirdparty_lines} lines')
print(f'Total: {engine_core_lines + engine_platform_lines + sandbox_lines + engine_thirdparty_lines} lines')
