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
#include <cctype>
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
const char altsep = 0;
#endif


using namespace ftx;

std::string _cwd()
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

std::string path::cwd()
{
	return _cwd();
}

std::tuple<std::string, std::string> path::splitext(const std::string &path)
{
	auto sep_index = path.rfind(sep);
	auto dot_index = path.rfind(extsep);

#ifdef WIN32
	if (altsep != 0)
	{
		auto altsep_index = path.rfind(altsep);
		if (altsep_index != std::string::npos)
		{
			if (sep_index == std::string::npos)
			{
				sep_index = altsep_index;
			}
			else
			{
				sep_index = max(sep_index, altsep_index);
			}
		}
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
				auto c = path[filename_index];
				if (c != sep && c != altsep)
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
		if (normp.substr(0, 2) == std::string() + sep + sep
			&& normp.substr(2, 1) != std::string() + sep)
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

#ifdef WIN32
std::tuple<std::string, std::string> _split_win32(const std::string &path)
{
	std::string drive;
	std::string rest;

	std::tie(drive, rest) = _splitdrive_win32(path);

	auto index = rest.size();
	while (index != 0)
	{
		auto c = rest[index - 1];
		if (c == sep || c == altsep)
		{
			break;
		}

		--index;
	}

	std::string head = rest.substr(0, index);
	std::string tail = rest.substr(index);

	std::string head2 = head;
	while (!head2.empty())
	{
		auto c = *(head2.rbegin());
		if (c == sep || c == altsep)
		{
			head2 = head2.substr(0, head2.size() - 1);
		}
		else
		{
			break;
		}
	}

	if (!head2.empty())
	{
		head = head2;
	}

	return std::make_tuple(drive + head, tail);
}
#else
std::tuple<std::string, std::string> _split_posix(const std::string &path)
{
	auto pos = path.rfind('/');

	if (pos == std::string::npos)
	{
		return std::tuple<std::string, std::string>(std::string(), path);
	}

	std::string head = path.substr(0, pos + 1);
	std::string tail = path.substr(pos + 1);

	for (auto c : head)
	{
		if (c != '/')
		{
			while (*(head.rbegin()) == '/')
			{
				head = head.substr(0, head.size() - 1);
				continue;
			}

			break;
		}
	}

	return std::make_tuple(head, tail);
}
#endif

std::tuple<std::string, std::string> path::split(const std::string &path)
{
#ifdef WIN32
	return _split_win32(path);
#else
	return _split_posix(path);
#endif
}

#ifdef WIN32
bool _isabs_win32(const std::string &path)
{
	std::string p;
	std::tie(std::ignore, p) = _splitdrive_win32(path);

	return p != "" && (p[0] == sep || p[0] == altsep);
}
#else
bool _isabs_posix(const std::string &path)
{
	return path[0] == sep;
}
#endif

bool path::isabs(const std::string &path)
{
#ifdef WIN32
	return _isabs_win32(path);
#else
	return _isabs_posix(path);
#endif
}

#ifdef WIN32
void _join_two_win32(std::string &result_drive, std::string &result_path, const std::string &rpath)
{
	std::string pdrive;
	std::string ppath;
	std::tie(pdrive, ppath) = _splitdrive_win32(rpath);
	if (!ppath.empty() && (ppath[0] == sep || ppath[0] == altsep))
	{
		if (!pdrive.empty() && result_drive.empty())
		{
			result_drive = pdrive;
		}
		result_path = ppath;
		return;
	}
	else if (!pdrive.empty() && pdrive != result_drive)
	{
		std::string lower_pdrive = pdrive;
		std::string lower_lpath = result_drive;
		std::transform(lower_pdrive.begin(), lower_pdrive.end(), lower_pdrive.begin(), std::tolower);
		std::transform(lower_lpath.begin(), lower_lpath.end(), lower_lpath.begin(), std::tolower);
		if (lower_pdrive != lower_lpath)
		{
			result_drive = pdrive;
			result_path = ppath;
			return;
		}
		result_drive = pdrive;
	}

	if (!result_path.empty())
	{
		auto c = *(result_path.rbegin());
		if (c != sep && c != altsep)
		{
			result_path += sep;
		}
		result_path += ppath;
	}
}

std::string _join_win32(const std::string &lpath, const std::string &rpath)
{
	std::string result_drive;
	std::string result_path;
	std::tie(result_drive, result_path) = _splitdrive_win32(lpath);
	_join_two_win32(result_drive, result_path, rpath);

	if (!result_drive.empty() && !result_path.empty())
	{
		auto pc = result_path[0];
		auto dc = *(result_drive.rbegin());
		if (pc != sep && pc != altsep && dc != ':')
		{
			return result_drive + sep + result_path;
		}
	}

	return result_drive + result_path;
}

std::string _join_win32(const std::string &lpath, const std::vector<std::string> &rpaths)
{
	std::string result_drive;
	std::string result_path;
	std::tie(result_drive, result_path) = _splitdrive_win32(lpath);
	for (auto rp : rpaths)
	{
		_join_two_win32(result_drive, result_path, rp);
	}

	if (!result_drive.empty() && !result_path.empty())
	{
		auto pc = result_path[0];
		auto dc = *(result_drive.rbegin());
		if (pc != sep && pc != altsep && dc != ':')
		{
			return result_drive + sep + result_path;
		}
	}

	return result_drive + result_path;
}
#else
void _join_two_posix(std::string &lpath, const std::string &rpath)
{
	if (_isabs_posix(rpath))
	{
		lpath = rpath;
	}
	else if (lpath.empty() || *(lpath.rbegin()) == sep || *(lpath.rbegin()) == altsep)
	{
		lpath += rpath;
	}
	else
	{
		lpath += sep + rpath;
	}
}

std::string _join_posix(const std::string &lpath, const std::string &rpath)
{
	std::string path = lpath;
	_join_two_posix(path, rpath);
	return path;
}

std::string _join_posix(const std::string &lpath, const std::vector<std::string> &rpaths)
{
	std::string path = lpath;
	for (auto rp : rpaths)
	{
		_join_two_posix(path, rp);
	}

	return path;
}
#endif

std::string path::join(const std::string &lpath, const std::string &rpath)
{
#ifdef WIN32
	return _join_win32(lpath, rpath);
#else
	return _join_posix(lpath, rpath);
#endif
}

std::string path::join(const std::string &lpath, const std::vector<std::string> &rpaths)
{
#ifdef WIN32
	return _join_win32(lpath, rpaths);
#else
	return _join_posix(lpath, rpaths);
#endif
}

std::string path::basename(const std::string &path)
{
	std::string basename;
	std::tie(std::ignore, basename) = split(path);

	return basename;
}

std::string path::dirname(const std::string &path)
{
	std::string dirname;
	std::tie(dirname, std::ignore) = split(path);

	return dirname;
}

std::string _join_str(const std::string& str, const std::vector<std::string>& arr)
{
	if (arr.empty())
	{
		return std::string();
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

#ifdef WIN32
std::string _normpath_win32(const std::string &path)
{
	std::string backslash = "\\";
	std::string dot = ".";

	std::string np = path;
	if (np.substr(0, 4) == "\\\\.\\" || np.substr(0, 4) == "\\\\?\\")
	{
		return path;
	}
	
	std::replace(np.begin(), np.end(), '/', '\\');

	std::string prefix;
	std::string pth;
	std::tie(prefix, pth) = _splitdrive_win32(np);

	if (prefix.empty())
	{
		while (pth[0] == '\\')
		{
			prefix += backslash;
			pth = pth.substr(1);
		}
	}
	else
	{
		if (pth[0] == '\\')
		{
			prefix += backslash;
			pth = pth.substr(1);
		}
	}

	if (pth.empty())
	{
		return prefix;
	}
	
	std::vector<std::string> comps;
	_split(pth, '\\', comps);
	
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
			else if (i == 0 && !prefix.empty() && *(prefix.rbegin()) == '\\')
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

	if (prefix.empty() && comps.empty())
	{
		comps.push_back(dot);
	}

	return prefix + _join_str(backslash, comps);
}
#else
std::string _normpath_posix(const std::string &path)
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
		if (comp.empty() || comp == ".")
		{
			continue;
		}

		if (comp != ".." || (initial_slashes == 0 && new_comps.empty()) || (!new_comps.empty() && *(new_comps.crbegin()) == ".."))
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
	else
	{
		if (new_comps.empty())
		{
			return curdir;
		}
	}	

	norm_path += _join_str(slash, new_comps);
	return norm_path;
}
#endif

std::string path::normpath(const std::string &path)
{
#ifdef WIN32
	return _normpath_win32(path);
#else
	return _normpath_posix(path);
#endif
}

#ifdef WIN32
std::string _abspath_win32(const std::string &path)
{
	std::string abs_path = path;

	char** lppPart = { NULL };
	char out_path[MAX_PATH] = {0};
	GetFullPathNameA(abs_path.c_str(), MAX_PATH, out_path, lppPart);
	abs_path = out_path;

	if (!_isabs_win32(abs_path))
	{
		abs_path = _join_win32(_cwd(), abs_path);
	}

	return _normpath_win32(abs_path);
}
#else
std::string _abspath_posix(const std::string &path)
{
	std::string abs_path = path;

	if (!_isabs_posix(abs_path))
	{
		abs_path = _join_posix(_cwd(), abs_path);
	}

	return _normpath_posix(abs_path);
}
#endif

std::string path::abspath(const std::string &path)
{
#ifdef WIN32
	return _abspath_win32(path);
#else
	return _abspath_posix(path);
#endif
}

#ifdef WIN32
std::tuple<std::string, std::string> _splitunc_win32(const std::string &path)
{
	std::string firstTwo;
	if (path[1] == ':')
	{
		goto EMPTY_PATH_TUPLE;
	}

	firstTwo = path.substr(0, 2);
	if (firstTwo == "//" || firstTwo == "\\\\")
	{
		std::string normp = path;
		std::replace(normp.begin(), normp.end(), '\\', '/');

		auto index = normp.find('/', 2);
		if (index <= 2)
		{
			goto EMPTY_PATH_TUPLE;
		}

		auto index2 = normp.find('/', index + 1);
		if (index2 == index + 1)
		{
			goto EMPTY_PATH_TUPLE;
		}

		if (index2 == std::string::npos)
		{
			index2 = path.size();
		}

		return std::make_tuple(path.substr(0, index2), path.substr(index2));
	}

EMPTY_PATH_TUPLE:
	return std::make_tuple(std::string(), path);
}

std::tuple<bool, std::string, std::vector<std::string>> _abspath_split(const std::string  path)
{
	std::string abs = _abspath_win32(_normpath_win32(path));
	
	std::string drive;
	std::string rest;

	std::tie(drive, rest) = _splitunc_win32(abs);
	bool is_unc = !drive.empty();
	if (!is_unc)
	{
		std::tie(drive, rest) = _splitdrive_win32(abs);
	}
	
	std::vector<std::string> path_list;
	_split(rest, sep, path_list);

	return std::make_tuple(is_unc, drive, path_list);
}

std::string _relpath_win32(const std::string &path, const std::string &start)
{
	std::string np = path;
	std::string ns = start.empty() ? curdir : start;

	if (path.empty())
	{
		return path;
	}
	
	bool s_is_unc, p_is_unc;
	std::string s_prefix, p_prefix;
	std::vector<std::string> s_list, p_list;
	std::tie(s_is_unc, s_prefix, s_list) = _abspath_split(start);
	std::tie(p_is_unc, p_prefix, p_list) = _abspath_split(path);
	
	if (s_is_unc ^ p_is_unc)
	{
		return path;
	}
	
	std::string lower_sprefix = s_prefix;
	std::string lower_pprefix = p_prefix;
	std::transform(lower_sprefix.begin(), lower_sprefix.end(), lower_sprefix.begin(), std::tolower);
	std::transform(lower_pprefix.begin(), lower_pprefix.end(), lower_pprefix.begin(), std::tolower);
	
	if (lower_sprefix != lower_pprefix)
	{
		return path;
	}
	
	int i = 0;
	int end = min(s_list.size(), p_list.size());
	for (; i < end; ++i)
	{
		std::string lower_snode = s_list[i];
		std::string lower_pnode = p_list[i];
		std::transform(lower_snode.begin(), lower_snode.end(), lower_snode.begin(), std::tolower);
		std::transform(lower_pnode.begin(), lower_pnode.end(), lower_pnode.begin(), std::tolower);

		if (lower_snode != lower_pnode)
		{
			break;
		}
	}
	
	std::vector<std::string> rel_list;
	for (int j = s_list.size() - i; j > 0; --j)
	{
		rel_list.push_back(pardir);
	}
	
	for (int k = i; k < p_list.size(); ++k)
	{
		rel_list.push_back(p_list[k]);
	}

	if (rel_list.empty())
	{
		return curdir;
	}

	std::string rel_path = rel_list[0];
	for (int i = 1; i < rel_list.size(); ++i)
	{
		rel_path += sep;
		rel_path += rel_list[i];
	}

	return rel_path;
}
#else
std::string _relpath_posix(const std::string &path, const std::string &start)
{
	std::string np = path;
	std::string ns = start.empty() ? curdir : start;

	std::vector<std::string> path_list;
	_split(_abspath_posix(np), sep, path_list);

	std::vector<std::string> start_list;
	_split(_abspath_posix(ns), sep, start_list);

	std::vector<std::string> rel_list;

	auto path_it = path_list.cbegin();
	auto start_it = start_list.cbegin();
	for (; path_it != path_list.cend() && start_it != start_list.cend(); ++path_it, ++start_it)
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
		_join_two_posix(rel_path, node);
	}

	return rel_path;
}
#endif

std::string path::relpath(const std::string &path, const std::string &start)
{
#ifdef WIN32
	return _relpath_win32(path, start);
#else
	return _relpath_posix(path, start);
#endif
}

void _make_path_list(const std::string& path, std::vector<std::string>& path_list)
{
#ifdef WIN32
	std::string abspath = _normpath_win32(_abspath_win32(path));
	std::tie(std::ignore, abspath) = _splitdrive_win32(abspath);
#else
	std::string abspath =  _normpath_posix(_abspath_posix(path));
#endif
	
	_split(abspath, sep, path_list);
	std::remove_if(path_list.begin(), path_list.end(), [](const std::string &node){
		return node.empty();
	});
}

std::vector<std::string> _make_path_list(const std::string& path)
{
	std::vector<std::string> path_list;
	_make_path_list(path, path_list);
	return path_list;
}

std::string path::commonprefix(const std::string &path1, const std::string &path2)
{
	if (path1.empty() || path2.empty())
	{
		return std::string();
	}

	std::string p1 = path1;
	std::string p2 = path2;

#ifdef WIN32
	std::string drive1, drive2;
	std::tie(drive1, p1) = _splitdrive_win32(_abspath_win32(p1));
	std::tie(drive2, p2) = _splitdrive_win32(_abspath_win32(p2));

	if (drive1 != drive2)
	{
		return std::string();
	}
#endif

	std::vector<std::string> path1_list = _make_path_list(p1);
	std::vector<std::string> path2_list = _make_path_list(p2);

	std::vector<std::string> common_list;
	for (auto i = 0; i < path1_list.size() && i < path2_list.size(); ++i)
	{
		std::string node1 = path1_list[i];
		std::string node2 = path2_list[i];
		if (node1 == node2)
		{
			common_list.push_back(node1);
		}
		else
		{
			break;
		}
	}

	std::string common_path;

#ifdef WIN32
	if (!drive1.empty())
	{
		common_path += drive1;
	}

	common_path += sep;
	common_path = _join_win32(common_path, common_list);
#else
	common_path += sep;
	common_path = _join_posix(common_path, common_list);
#endif

	return common_path;
}

#ifndef MAXUINT32
#define MAXUINT32 (-1)
#endif

std::string path::commonprefix(const std::vector<std::string> &path_list)
{
	if (path_list.empty())
	{
		return std::string();
	}

	std::vector<std::string> paths = path_list;
#ifdef WIN32
	std::string common_drive;
	bool is_init = false;
	std::vector<std::string> tails;
#endif
	for (std::string path : paths)
	{
		if (path.empty())
		{
			return std::string();
		}

#ifdef WIN32
		std::string drive;
		std::string tail;
		std::tie(drive, tail) = _splitdrive_win32(_abspath_win32(path));

		if (!is_init)
		{
			common_drive = drive;
			is_init = true;
		}
		else
		{
			if (drive != common_drive)
			{
				return std::string();
			}
		}

		tails.push_back(tail);
	}

	paths = tails;
#else
	}
#endif

	std::vector<std::vector<std::string>> path_list_table;
	size_t min_size = MAXUINT32;
	for (std::string path : paths)
	{
		std::vector<std::string> list = _make_path_list(path);
		if (list.size() < min_size)
		{
			min_size = list.size();
		}
		path_list_table.push_back(list);
	}

	std::vector<std::string> common_list;
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

		common_list.push_back(common_node);
	}

ENDING:

	std::string common_path;

#ifdef WIN32
	if (!common_drive.empty())
	{
		common_path += common_drive;
	}

	common_path += sep;
	common_path = _join_win32(common_path, common_list);
#else
	common_path += sep;
	common_path = _join_posix(common_path, common_list);
#endif

	return common_path;
}

#ifdef WIN32
std::vector<std::string> _listdir_win32(const std::string &path)
{
	std::vector<std::string> list_dir;

	std::string strFind = _join_win32(path, "*.*");
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = FindFirstFileA(strFind.c_str(), &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return list_dir;
	}

	do
	{
		std::string name = FindFileData.cFileName;
		if (name == curdir || name == pardir)
		{
			continue;
		}
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

std::vector<std::string> path::listdir(const std::string &path)
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

bool path::isdir(const std::string &path)
{
	struct stat buf;
	return stat(path.c_str(), &buf) == 0 && S_ISDIR(buf.st_mode);
}

bool path::isfile(const std::string &path)
{
	struct stat buf;
	return stat(path.c_str(), &buf) == 0 && S_ISREG(buf.st_mode);
}

bool path::exists(const std::string &path)
{
	struct stat buf;
	return stat(path.c_str(), &buf) == 0;
}

int path::cd(const std::string &path)
{
	return chdir(path.c_str());
}

void path::makedirs(const std::string &path)
{
	std::string npath = normpath(abspath(path));
	
	std::string temp_path;
#ifdef WIN32
	std::tie(temp_path, npath) = splitdrive(npath);
	if (temp_path.empty())
	{
		return;
	}	
#endif
	temp_path += + sep;
	
	auto node_list = _split(npath, sep);
	for (auto node : node_list)
	{
		temp_path = join(temp_path, node);
		if (!isdir(temp_path))
		{
#ifdef WIN32
			mkdir(temp_path.c_str());
#else
			mkdir(temp_path.c_str(), ACCESSPERMS);
#endif
		}
	}
}

void path::rmtree(const std::string &path)
{
	if (!isdir(path))
	{
		remove(path.c_str());
	}
	
	std::string temp_path = relpath(path);
	auto nodes = listdir(temp_path);
	while (nodes.size() != 0)
	{
		std::string node_path = join(temp_path, nodes[0]);

		if (isdir(node_path))
		{
			auto temp_nodes = listdir(node_path);
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

		nodes = listdir(temp_path);
		
		while (nodes.size() == 0)
		{
			std::string root;
			std::string node;
			std::tie(root, node) = split(relpath(temp_path, path));

			if (node.empty() || node == curdir || root.find(pardir) != std::string::npos)
			{
				break;
			}

			rmdir(temp_path.c_str());

			temp_path = join(path, root);
			nodes = listdir(temp_path);
		}
	}
	
	rmdir(path.c_str());
}

PathGenerator path::walk(const std::string &path)
{
	return PathGenerator(path);
}

void path::walk(const std::string &path, std::function<void(std::string root, std::vector<std::string> folders, std::vector<std::string> files)> func)
{
	for (auto p : walk(path))
	{
		std::string root;
		std::vector<std::string> folders;
		std::vector<std::string> files;

		std::tie(root, folders, files) = p;
		func(root, folders, files);
	}
}
