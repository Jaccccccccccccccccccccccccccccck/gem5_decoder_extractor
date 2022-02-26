import os
import shutil

gem5_base_dir = '/home/workspace/gem5/'
compiled_gem5_base_dir = '/home/workspace/gem5/build/POWER/'
decoder_project_base_dir = '/home/workspace/gem5_decoder_extract/'
includes = []
processed_includes = set()


def analyse_includes(base_paths):
    for base_path in base_paths:
        if not os.path.exists(os.path.dirname(base_path)):
                os.makedirs(os.path.dirname(base_path))
        shutil.copy(os.path.join(compiled_gem5_base_dir, base_path), os.path.join(base_path))
        open_and_extract_includes(base_path)
    while includes:
        include_info = includes.pop()
        if include_info['source_rel_dir'] + include_info['include'] not in processed_includes:
            processed_includes.add(
                include_info['source_rel_dir'] + include_info['include'])
            print("extract include from {}".format(include_info))
            finded_file_paths = find_and_copy_include(
                include_info['include'], include_info['source_rel_dir'], )
            if finded_file_paths:
                print("copy file path success: {}".format(finded_file_paths))
                for finded_file_path in finded_file_paths:
                    open_and_extract_includes(finded_file_path)
            else:
                print("cannot find file path!")


def find_and_copy_include(include: str, project_rel_path: str):
    if(os.path.exists(os.path.join(compiled_gem5_base_dir, project_rel_path, include))):  # 在同级目录
        if not os.path.exists(os.path.dirname(os.path.join(project_rel_path, include))):
            os.makedirs(os.path.dirname(os.path.join(project_rel_path, include)))
        shutil.copy(os.path.join(compiled_gem5_base_dir, project_rel_path,include), 
                    os.path.join(project_rel_path, include))
        if os.path.exists(os.path.join(compiled_gem5_base_dir, project_rel_path,include.replace('.hh', '.cc'))):
            shutil.copy(os.path.join(compiled_gem5_base_dir, project_rel_path,include.replace('.hh', '.cc')), 
                    os.path.join(project_rel_path, include.replace('.hh', '.cc')))
            return [os.path.join(project_rel_path, include), os.path.join(project_rel_path, include.replace('.hh', '.cc'))]
        else:
            return [os.path.join(project_rel_path, include), ]
        
    elif(os.path.exists(os.path.join(compiled_gem5_base_dir, include))): # 在项目目录
        if not os.path.exists(os.path.dirname(os.path.join(decoder_project_base_dir, include))):
            os.makedirs(os.path.dirname(os.path.join(decoder_project_base_dir, include)))
        shutil.copy(os.path.join(compiled_gem5_base_dir, include),
                    os.path.join(decoder_project_base_dir, include))
        if os.path.exists(os.path.join(compiled_gem5_base_dir, include.replace('.hh', '.cc'))):
            shutil.copy(os.path.join(compiled_gem5_base_dir, include.replace('.hh', '.cc')),
                    os.path.join(decoder_project_base_dir, include.replace('.hh', '.cc')))
            return [include, include.replace('.hh', '.cc')]
        else:
            return [include, ]
    else:
        print("can't find include: {} in file: {}".format(
            include, project_rel_path))
        return False


def open_and_extract_includes(project_rel_path: str):
    print("get include from {}".format(project_rel_path))
    with open(os.path.join(compiled_gem5_base_dir, project_rel_path)) as f:
        for line in f.readlines():
            if line.startswith('#include "'):
                index_1 = line.find('"')
                include = line[index_1 + 1: len(line) - 2]
                includes.append(
                    {
                        'include': include,  # include语句中的字符串
                        # 当前依赖的源文件的项目相对路径
                        'source_rel_dir': os.path.dirname(project_rel_path),
                    }
                )
                print("include: {}".format(include))


def copy_ext_include():
    if not os.path.exists(os.path.join(decoder_project_base_dir, 'ext')):
        shutil.copytree(os.path.join(gem5_base_dir, 'ext'),
                        os.path.join(decoder_project_base_dir, 'ext')
                        )
    if not os.path.exists(os.path.join(decoder_project_base_dir, 'include')):
        shutil.copytree(os.path.join(gem5_base_dir, 'include'),
                        os.path.join(decoder_project_base_dir, 'include')
                        )


if __name__ == "__main__":
    copy_ext_include()
    analyse_includes([
        'arch/power/generated/generic_cpu_exec.cc', 
        'arch/power/generated/inst-constrs.cc', 
        'sim/init.cc', 
        'sim/tags.cc', 
        'sim/backtrace_glibc.cc', 
        'python/pybind11/core.cc', 
        'python/pybind11/debug.cc', 
        'python/pybind11/event.cc', 
        'python/pybind11/stats.cc', 
        'base/date.cc',
        'base/version.cc',
        ])
