// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"

#include "RouteResult.h"
#include "RouteParameters.h"
#include "RouteItem.h"

#include "osrm/json_container.hpp"
#include "engine/polyline_compressor.hpp"
#include <msclr\marshal_cppstd.h>

using namespace Osrmnet::Route;
using namespace osrm::util::json;

RouteResult^ RouteResult::FromJsonObject(const osrm::util::json::Object& jsonObject, RouteParameters^ routeParams)
{
	auto result = gcnew RouteResult();

	// Code
	auto codeJson = jsonObject.values.at("code").get<String>().value;
	result->Code = msclr::interop::marshal_as<System::String^>(codeJson);
	
	// Process Routes
	const auto &routesJson = jsonObject.values.at("routes").get<Array>().values;
	for (const auto &route : routesJson)
	{
		const auto &routeObj = route.get<osrm::util::json::Object>();
		result->Routes->Add(RouteItem::FromJsonObject(routeObj, routeParams));
	}

	// Process waypoint


	return result;
}