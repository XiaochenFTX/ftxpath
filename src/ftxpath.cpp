//
//  ftxpath.cpp
//  ftxpath
//
//  Created by 王晓辰 on 15/8/8.
//  Copyright (c) 2015年 ftxtool. All rights reserved.
//

#include "ftxpath.h"

#include "split.h"

#include <string>
#include <cstdlib>
#include <algorithm>
#include <sys/stat.h>

#ifdef WIN32
#include <direct.h>
#include <Windows.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif


const std::string curdir = ".";
const std::string pardir = "..";
const std::string extsep = ".";
#ifdef WIN32
const char sep = '\\';
const char altsep = '/';
#else
const char sep = '/';
#endif


using namespace ftx;

std::string path::cwd()
{
	char* buff = nullptr;
	buff = getcwd(nullptr, 0);

	std::string path(buff);

	if (buff != nullptr)
	{
		free(buff);
	}

	return path;
}

std::tuple<std::string, std::string> path::split(const std::string &path)
{

}

std::tuple<std::string, std::string> path::splitext(const std::string &path)
{
	auto sep_index = path.rfind(sep);
	auto dot_index = path.rfind(extsep);

#ifdef WIN32
	if (altsep != 0)
	{
		auto altsep_index = path.rfind(altsep);
		sep_index = max(sep_index, altsep_index);
	}
#endif

	if (dot_index != std::string::npos)
	{
		if (sep_index == std::string::npos)
		{
			return std::make_tuple(path.substr(0, dot_index), path.substr(dot_index));
		}

		if (dot_index > sep_index)
		{
			auto filename_index = sep_index + 1;
			while (filename_index < dot_index)
			{
				if (path.substr(filename_index, 1) != std::string("" + sep))
				{
					return std::make_tuple(path.substr(0, dot_index), path.substr(dot_index));
				}

				++filename_index;
			}
		}
	}

	return std::make_tuple(path, std::string());
}

#ifdef WIN32
std::tuple<std::string, std::string> _splitdrive_win32(const std::string&path)
{
	std::string drive = "";
	std::string np = path;

	if (np.size() > 1)
	{
		std::replace(np.begin(), np.end(), altsep, sep);
		std::string normp = np;
		if (normp.substr(0, 2) == std::string("" + sep) + sep
			&& normp.substr(2, 1) != std::string("" + sep))
		{
			auto index = normp.find(sep, 2);
			if (index == std::string::npos)
			{
				goto EMPTY_RETURN;
			}

			auto index2 = normp.find(sep, index + 1);
			if (index2 == index + 1)
			{
				goto EMPTY_RETURN;
			}

			if (index2 == std::string::npos)
			{
				index2 = path.size();
			}

			drive = path.substr(0, index2);
			std::string p = path.substr(index2);

			return std::make_tuple(drive, p);
		}

		if (normp[1] == ':')
		{
			drive = path.substr(0, 2);
			std::string p = path.substr(2);

			return std::make_tuple(drive, p);
		}
	}

EMPTY_RETURN:
	return std::make_tuple(drive, path);
}
#endif

std::tuple<std::string, std::string> path::splitdrive(const std::string &path)
{
#ifdef WIN32
	return _splitdrive_win32(path);
#else
	return std::make_tuple("", path);
#endif
}

// =============================================================
std::string ftxpath::cwd()
{
	char* buff = nullptr;

//#ifdef WIN32
//	buff = _getcwd(nullptr, 0);
//#else
    buff = getcwd(nullptr, 0);
//#endif

	std::string path(buff);

	if (buff != nullptr)
	{
		free(buff);
	}
    
    return path;
}

bool ftxpath::isabs(const std::string &path)
{
#ifdef WIN32
	std::string drive;
	std::string p;
	std::tie(drive, p) = splitdrive(path);

	return drive != "" && p != "" && (p[0] == sep || p[0] == altsep);
#else
    return path[0]=='/';
#endif
}

void _join(std::string& lpath, const std::string& rpth)
{
    if (ftxpath::isabs(rpth))
    {
        lpath = rpth;
    }
	else if (lpath.empty() || *(lpath.rbegin()) == sep || *(lpath.rbegin()) == altsep)
    {
        lpath += rpth;
    }
    else
    {
        lpath += sep + rpth;
    }

}

std::string _join_str(const std::string& str, const std::vector<std::string>& arr)
{
    if (arr.empty())
    {
        return "";
    }
    
    std::string result;
    for (auto iter = arr.cbegin();;)
    {
        result += *iter;
        if (++iter != arr.cend())
        {
            result += str;
        }
        else
        {
            break;
        }
    }
    
    return result;
}

std::string ftxpath::join(const std::string &lpath, const std::string &rpath)
{
    std::string path = lpath;
    _join(path, rpath);
    return path;
}

std::string ftxpath::join(const std::string &lpath, const std::vector<std::string> &rpaths)
{
    std::string path = lpath;
    
    for (auto rp: rpaths)
    {
        _join(path, rp);
    }
    
    return path;
}

std::string ftxpath::basename(const std::string &path)
{
    auto pos = path.find_last_of('/');    
    return path.substr(pos + 1);
}

std::string ftxpath::dirname(const std::string &path)
{
    if (path == "/")
    {
        return path;
    }

    auto pos = path.find_last_of('/');

    if (pos == std::string::npos)
    {
        return std::string();
    }

    return path.substr(0, pos);
}

std::tuple<std::string, std::string> ftxpath::split(const std::string &path)
{
    if (path == "/")
    {
        return std::tuple<std::string, std::string>(path, "");
    }

    auto pos = path.find_last_of('/');

    if (pos == std::string::npos)
    {
        return std::tuple<std::string, std::string>("", path);
    }

	return std::make_tuple(path.substr(0, pos), path.substr(pos + 1));
}

#ifdef WIN32
#include <iostream>
std::string _normpath_win32(const std::string& path)
{
	std::cout << "bbbb" << std::endl;
	std::string backslash = "\\";
	std::string dot = ".";

	std::string np = path;
	if (np.substr(0, 4) == "\\\\.\\" || np.substr(0, 4) == "\\\\?\\")
	{
		std::cout << "111111" << std::endl;
		return path;
	}
	std::cout << "zzzzz" << std::endl;
	std::replace(np.begin(), np.end(), '/', '\\');

	std::string prefix;
	std::string pth;
	std::tie(prefix, pth) = ftxpath::splitdrive(np);

	if (pth.empty())
	{
		std::cout << "222222222" << std::endl;
		return prefix;
	}
	std::cout << "zzzzz" << std::endl;
	while (pth.substr(0, 1) == "\\")
	{
		prefix = prefix + backslash;
		pth = pth.substr(1);
	}

	std::vector<std::string> comps;
	_split(pth, '\\', comps);
	std::cout << "zzzzz" << std::endl;
	int i = 0;
	while (i < comps.size())
	{
		if (comps[i] == "." || comps[i] == "")
		{
			comps.erase(comps.begin() + i);
		}
		else if (comps[i] == "..")
		{
			if (i > 0 && comps[i - 1] != "..")
			{
				comps.erase(comps.begin() + i - 1);
				comps.erase(comps.begin() + i - 1);
				--i;
			}
			else if (i == 0 && *(prefix.rbegin()) == '\\')
			{
				comps.erase(comps.begin() + i);
			}
			else
			{
				++i;
			}
		}
		else
		{
			++i;
		}
	}

	std::cout << "zzzzz" << std::endl;

	std::string nromp = prefix + ftxpath::join(backslash, comps);

	std::cout << "nrom: " << nromp << std::endl;

	return nromp;
}
#else
std::string _normpath_posix(const std::string& path)
{
	if (path.empty())
	{
		return curdir;
	}

	int initial_slashes = 0;
	if (path[0] == '/')
	{
		initial_slashes = 1;
	}

	if (initial_slashes == 1 && path[1] == '/' && path[2] != '/')
	{
		initial_slashes = 2;
	}

	std::vector<std::string> comps;
	_split(path, '/', comps);

	std::vector<std::string> new_comps;
	for (auto comp : comps)
	{
		if (comp.empty() || comp == curdir)
		{
			continue;
		}

		if (comp != pardir || (initial_slashes == 0 && new_comps.empty()) || (!new_comps.empty() && *(new_comps.crbegin()) == pardir))
		{
			new_comps.push_back(comp);
		}
		else if (!new_comps.empty())
		{
			new_comps.pop_back();
		}
	}

	std::string slash = "/";
	std::string norm_path;
	if (initial_slashes != 0)
	{
		for (int i = 0; i < initial_slashes; ++i)
		{
			norm_path += slash;
		}
	}

	norm_path += _join_str(slash, new_comps);
	return norm_path;
}
#endif

std::string ftxpath::normpath(const std::string &path)
{
#ifdef WIN32
	return _normpath_win32(path);
#else
	return _normpath_posix(path);
#endif
}

std::string ftxpath::abspath(const std::string &path)
{
    std::string abs_path = path;
    if (!isabs(abs_path))
    {
        abs_path = join(cwd(), path);
    }
    return normpath(abs_path);
}

#ifdef WIN32
std::tuple<std::string, std::vector<std::string>> _abspath_split(const std::string& path)
{
	std::string abs = ftxpath::abspath(ftxpath::normpath(path));
	std::string drive;
	std::string rest;
	std::tie(drive, rest) = ftxpath::splitdrive(abs);
	
	std::vector<std::string> path_list;
	_split(rest, sep, path_list);

	return std::make_tuple(drive, path_list);
}
#endif

std::string ftxpath::relpath(const std::string &path, const std::string &start)
{
	std::string np = path;
	std::string ns = start;

#ifdef WIN32
	std::replace(np.begin(), np.end(), altsep, sep);
	std::replace(ns.begin(), ns.end(), altsep, sep);
#endif

    std::vector<std::string> path_list;
    _split(abspath(np), sep, path_list);
    
    std::vector<std::string> start_list;
    _split(abspath(ns), sep, start_list);
    
    std::vector<std::string> rel_list;
    
    auto path_it = path_list.cbegin();
    auto start_it = start_list.cbegin();
    for (;path_it != path_list.cend() && start_it != start_list.cend(); ++path_it, ++start_it)
    {
        if (*path_it != *start_it)
        {
            break;
        }
    }

    for (; start_it != start_list.cend(); ++start_it)
    {
        rel_list.push_back(pardir);
    }
    
    for (; path_it != path_list.cend(); ++path_it)
    {
        rel_list.push_back(*path_it);
    }
    
    std::string rel_path;
    for (auto node : rel_list)
    {
        _join(rel_path, node);
    }
    
    return rel_path;
}

#ifdef WIN32
std::vector<std::string> _listdir_win32(const std::string &path)
{
	std::vector<std::string> list_dir;

	std::string strFind = ftxpath::join(path, "*.*");
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = FindFirstFileA(strFind.c_str(), &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return list_dir;
	}

	do
	{
		std::string name = FindFileData.cFileName;
		list_dir.push_back(name);
	} while (FindNextFileA(hFind, &FindFileData));

	FindClose(hFind);

	return list_dir;
}
#else
std::vector<std::string> _listdir_posix(const std::string &path)
{
	std::vector<std::string> list_dir;
	DIR* pDir = opendir(path.c_str());
	if (pDir != nullptr)
	{
		struct dirent *ent;
		while ((ent = readdir(pDir)) != nullptr)
		{
			std::string name = ent->d_name;
			if (name == curdir || name == pardir)
			{
				continue;
			}
			list_dir.push_back(ent->d_name);
		}
		closedir(pDir);
	}

	return list_dir;
}
#endif

std::vector<std::string> ftxpath::listdir(const std::string &path)
{
#ifdef WIN32
	return _listdir_win32(path);
#else
	return _listdir_posix(path);
#endif
}

#ifdef WIN32
#define S_ISDIR(st_mode) (_S_IFDIR & st_mode)
#define S_ISREG(st_mode) (_S_IFREG & st_mode)
#endif

bool ftxpath::isdir(const std::string &path)
{
    struct stat buf;
    return stat(path.c_str(), &buf) == 0 && S_ISDIR(buf.st_mode);
}

bool ftxpath::isfile(const std::string &path)
{
    struct stat buf;
    return stat(path.c_str(), &buf) == 0 && S_ISREG(buf.st_mode);
}

PathGenerator ftxpath::walk(const std::string &path)
{
    return PathGenerator(path);
}

void ftxpath::walk(const std::string &path, std::function<void(std::string root, std::vector<std::string> folders, std::vector<std::string> files)> func)
{
    for (auto p : walk(path))
    {
        func(std::get<0>(p), std::get<1>(p), std::get<2>(p));
    }
}

bool ftxpath::exists(const std::string &path)
{
    struct stat buf;
    return stat(path.c_str(), &buf) == 0;
}

void _make_path_list(const std::string& path, std::vector<std::string>& path_list)
{
    std::string abspath = ftxpath::normpath(ftxpath::abspath(path));
    _split(abspath, '/', path_list);
}

std::vector<std::string> _make_path_list(const std::string& path)
{
    std::vector<std::string> path_list;
    _make_path_list(path, path_list);
    return path_list;
}

std::string ftxpath::commonprefix(const std::string &path1,  const std::string &path2)
{
    if (path1.empty() || path2.empty())
    {
        return std::string();
    }

    std::vector<std::string> path1_list = _make_path_list(path1);
    std::vector<std::string> path2_list = _make_path_list(path2);

    std::string common_path;
    for (auto i = 0; i < path1_list.size() && i < path2_list.size(); ++i)
    {
        std::string node1 = path1_list[i];
        std::string node2 = path2_list[i];
        if (node1 == node2)
        {
            _join(common_path, node1);
        }
        else
        {
            break;
        }
    }

    if (!common_path.empty())
    {
        common_path = "/" + common_path;
    }

    return common_path;
}

std::string ftxpath::commonprefix(std::vector<std::string> path_list)
{
    if (path_list.empty())
    {
        return std::string();
    }

    for (std::string path : path_list)
    {
        if (path.empty())
        {
            return std::string();
        }
    }

    std::vector<std::vector<std::string>> path_list_table;
	size_t min_size = MAXUINT32;
    for (std::string path : path_list)
    {
        std::vector<std::string> list = _make_path_list(path);
        if (list.size() < min_size)
        {
            min_size = list.size();
        }
        path_list_table.push_back(list);
    }

    std::string common_path;
    for (auto i = 0; i < min_size; ++i)
    {
        std::string common_node;
        for (auto list : path_list_table)
        {
            std::string node = list[i];
            if (common_node.empty())
            {
                common_node = node;
                continue;
            }

            if (node != common_node)
            {
                goto ENDING;
            }
        }

        _join(common_path, common_node);
    }

ENDING:

    if (!common_path.empty())
    {
        common_path = std::string("" + sep) + common_path;
    }

    return common_path;
}

std::tuple<std::string, std::string> ftxpath::splitext(const std::string &path)
{
    auto sep_index = path.rfind(sep);
    auto dot_index = path.rfind(extsep);

    if (dot_index != std::string::npos)
    {
        if (sep_index == std::string::npos)
        {
            return std::make_tuple(path.substr(0, dot_index), path.substr(dot_index));
        }

        if (dot_index > sep_index)
        {
            auto filename_index = sep_index + 1;
            while (filename_index < dot_index)
            {
                if (path.substr(filename_index, 1) != std::string("" + sep))
                {
                    return std::make_tuple(path.substr(0, dot_index), path.substr(dot_index));
                }

                filename_index++;
            }
        }
    }

    return std::make_tuple(path, std::string());
}

std::tuple<std::string, std::string> ftxpath::splitdrive(const std::string&path)
{
#ifdef WIN32
	return _splitdrive_win32(path);
#else
	return std::make_tuple("", path);
#endif
}

int ftxpath::cd(const std::string &path) {
    return chdir(path.c_str());
}

void ftxpath::makedirs(const std::string &path) {
    std::string abspath = ftxpath::normpath(ftxpath::abspath(path));

    std::string temp_path = "";
#ifdef WIN32
	std::tie(temp_path, std::ignore) = splitdrive(abspath);
	if (temp_path == "")
	{
		return;
	}
#else
	temp_path = "" + sep;
#endif

    for (auto node : _split(abspath, '/'))
    {
        temp_path = ftxpath::join(temp_path, node);
        if (!ftxpath::isdir(temp_path))
        {
#ifdef WIN32
			mkdir(temp_path.c_str());
#else
            mkdir(temp_path.c_str(), ACCESSPERMS);
#endif
        }
    }
}

void ftxpath::rmtree(const std::string &path) {
    if (!ftxpath::isdir(path))
    {
        remove(path.c_str());
    }

    std::string temp_path = ftxpath::relpath(path);
    auto nodes = ftxpath::listdir(temp_path);
    while (nodes.size() != 0)
    {
        std::string node_path = ftxpath::join(temp_path, nodes[0]);

        if (ftxpath::isdir(node_path))
        {
            auto temp_nodes = ftxpath::listdir(node_path);
            if (temp_nodes.size() == 0)
            {
                rmdir(node_path.c_str());
            }
            else
            {
                temp_path = node_path;
            }
        }
        else
        {
            remove(node_path.c_str());
        }

        nodes = ftxpath::listdir(temp_path);
        while(nodes.size() == 0)
        {
            std::string root;
            std::string node;
            std::tie(root, node) = ftxpath::split(ftxpath::relpath(temp_path, path));

            if (node.empty() || root.find(pardir) != std::string::npos)
            {
                break;
            }

            rmdir(temp_path.c_str());

            temp_path = ftxpath::join(path, root);
            nodes = ftxpath::listdir(temp_path);
        }
    }

    rmdir(path.c_str());
}
