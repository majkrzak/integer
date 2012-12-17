#pragma once
//     Simple C++ binding of GNU Multiple Precision Arithmetic Library Integers.
//     Copyright (C) 2012  Piotr Majkrzak <petrol.91@gmail.com>
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "integer.hpp"
#include <yaml-cpp/yaml.h>

namespace YAML
{
	template<>
	struct convert<Integer>
	{
		static Node encode ( const Integer& integer )
		{
			return Node(std::string ( integer ));
		}
		static bool decode ( const Node& node, Integer& integer )
		{
			integer = Integer ( node.as<std::string>() );
			return true;
		}
	};
}
