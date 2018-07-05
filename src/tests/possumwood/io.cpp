#include <dependency_graph/rtti.h>
#include <dependency_graph/data.h>

#include <actions/io.h>

#include "io.h"

namespace dependency_graph { namespace io {

bool isSaveable(const dependency_graph::BaseData& data) {
	return true;
}

} }

namespace possumwood { namespace io {

void fromJson(const json& j, dependency_graph::BaseData& data) {
	if(data.type() == "float") {
		dependency_graph::Data<float>& typed = dynamic_cast<dependency_graph::Data<float>&>(data);
		typed.value = j.get<float>();
	}
	else if(data.type() == dependency_graph::unmangledTypeId<std::string>()) {
		dependency_graph::Data<std::string>& typed = dynamic_cast<dependency_graph::Data<std::string>&>(data);
		typed.value = j.get<std::string>();
	}
	else
		assert(false);
}

void toJson(json& j, const dependency_graph::BaseData& data) {
	if(data.type() == "float") {
		const dependency_graph::Data<float>& typed = dynamic_cast<const dependency_graph::Data<float>&>(data);
		j = typed.value;
	}
	else if(data.type() == dependency_graph::unmangledTypeId<std::string>()) {
		const dependency_graph::Data<std::string>& typed = dynamic_cast<const dependency_graph::Data<std::string>&>(data);
		j = typed.value;
	}
	else
		assert(false);
}

bool isSaveable(const dependency_graph::BaseData& data) {
	return true;
}

} }
