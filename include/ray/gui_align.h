// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_GUI_WIDGET_ALIGN_H_
#define _H_GUI_WIDGET_ALIGN_H_

#include <ray/gui_types.h>

_NAME_BEGIN

class EXPORT GuiWidgetAlign
{
public:
	typedef std::map<std::string, int> MapAlign;

	enum Enum
	{
		HCenter = 0,
		VCenter = 0,
		Center = HCenter | VCenter,

		Left = 1 << 0,
		Right = 1 << 1,
		HStretch = Left | Right,

		Top = 1 << 2,
		Bottom = 1 << 3,
		VStretch = Top | Bottom,

		Stretch = HStretch | VStretch,
		Default = Left | Top
	};

	GuiWidgetAlign(Enum _value = Default)
		: _value(_value)
	{
	}

	bool isHCenter() const { return HCenter == (_value & ((int)HStretch)); }
	bool isVCenter() const { return VCenter == (_value & ((int)VStretch)); }
	bool isCenter() const { return Center == (_value & ((int)Stretch)); }
	bool isLeft() const { return Left == (_value & ((int)HStretch)); }
	bool isRight() const { return Right == (_value & ((int)HStretch)); }
	bool isHStretch() const { return HStretch == (_value & ((int)HStretch)); }
	bool isTop() const { return Top == (_value & ((int)VStretch)); }
	bool isBottom() const { return (Bottom == (_value & ((int)VStretch))); }
	bool isVStretch() const { return (VStretch == (_value & ((int)VStretch))); }
	bool isStretch() const { return (Stretch == (_value & ((int)Stretch))); }
	bool isDefault() const { return (Default == (_value & ((int)Stretch))); }

	GuiWidgetAlign& operator |= (const GuiWidgetAlign& _other)
	{
		_value = Enum(int(_value) | int(_other._value));
		return *this;
	}

	static GuiWidgetAlign parse(const std::string& value)
	{
		GuiWidgetAlign result(Default);
		const MapAlign& map_names = result.getValueNames();
		std::vector<std::string> vec;
		util::split(vec, value);

		for (auto& it : vec)
		{
			auto iter = map_names.find(it);
			if (iter != map_names.end())
			{
				result._value = Enum(int(result._value) | int(iter->second));
			}
		}

		return result;
	}

	std::string print() const
	{
		std::string result;

		if (_value & Left)
		{
			if (_value & Right)
				result = "HStretch";
			else
				result = "Left";
		}
		else if (_value & Right)
			result = "Right";
		else
			result = "HCenter";

		if (_value & Top)
		{
			if (_value & Bottom)
				result += " VStretch";
			else
				result += " Top";
		}
		else if (_value & Bottom)
			result += " Bottom";
		else
			result += " VCenter";

		return result;
	}

	int getValue() const
	{
		return _value;
	}

	const MapAlign& getValueNames() const
	{
		static MapAlign map_names;

		if (map_names.empty())
		{
			map_names["HCenter"] = HCenter;
			map_names["VCenter"] = VCenter;
			map_names["Center"] = Center;
			map_names["Left"] = Left;
			map_names["Right"] = Right;
			map_names["HStretch"] = HStretch;
			map_names["Top"] = Top;
			map_names["Bottom"] = Bottom;
			map_names["VStretch"] = VStretch;
			map_names["Stretch"] = Stretch;
			map_names["Default"] = Default;
		}

		return map_names;
	}

public:
	Enum _value;
};

inline GuiWidgetAlign operator | (const GuiWidgetAlign::Enum& a, const GuiWidgetAlign::Enum& b)
{
	return GuiWidgetAlign(GuiWidgetAlign::Enum(int(a) | int(b)));
}

inline GuiWidgetAlign operator | (const GuiWidgetAlign& a, const GuiWidgetAlign& b)
{
	return GuiWidgetAlign(GuiWidgetAlign::Enum(int(a._value) | int(b._value)));
}

inline bool operator == (const GuiWidgetAlign& a, const GuiWidgetAlign& b)
{
	return a._value == b._value;
}

inline bool operator != (const GuiWidgetAlign& a, const GuiWidgetAlign& b)
{
	return a._value != b._value;
}

inline std::ostream& operator << (std::ostream& stream, const GuiWidgetAlign&  value)
{
	stream << value.print();
	return stream;
}

inline std::istream& operator >> (std::istream& stream, GuiWidgetAlign&  result)
{
	result._value = GuiWidgetAlign::Enum(0);
	std::string value;
	stream >> value;

	const GuiWidgetAlign::MapAlign& map_names = result.getValueNames();
	GuiWidgetAlign::MapAlign::const_iterator iter = map_names.find(value);
	if (iter != map_names.end())
		result._value = GuiWidgetAlign::Enum(int(result._value) | int(iter->second));

	if (!stream.eof())
	{
		std::string value2;
		stream >> value2;
		iter = map_names.find(value2);
		if (iter != map_names.end())
			result._value = GuiWidgetAlign::Enum(int(result._value) | int(iter->second));
	}

	return stream;
}

struct EXPORT GuiFlowDirection
{
	enum Enum
	{
		LeftToRight,
		RightToLeft,
		TopToBottom,
		BottomToTop,
		MAX
	};

	GuiFlowDirection(Enum _value = LeftToRight) :
		_value(_value)
	{
	}

	static GuiFlowDirection parse(const std::string& str)
	{
		GuiFlowDirection type;
		int value = 0;
		for (;;)
		{
			const char* name = type.getValueName(value);
			if (strcmp(name, "") == 0 || name == str) break;
			value++;
		}
		type._value = (Enum)value;
		return type;
	}

	bool isHorizontal() const
	{
		return _value == LeftToRight || _value == RightToLeft;
	}

	bool isVertical() const
	{
		return !this->isHorizontal();
	}

	std::string print() const
	{
		return getValueName(_value);
	}

	int getValue() const
	{
		return _value;
	}

	const char* getValueName(int index) const
	{
		static const char* values[MAX + 1] = { "LeftToRight", "RightToLeft", "TopToBottom", "BottomToTop", "" };
		return values[(index < MAX && index >= 0) ? index : MAX];
	}

	Enum _value;
};

inline bool operator == (GuiFlowDirection const& a, GuiFlowDirection const& b)
{
	return a._value == b._value;
}

inline bool operator != (GuiFlowDirection const& a, GuiFlowDirection const& b)
{
	return a._value != b._value;
}

inline std::ostream& operator << (std::ostream& _stream, const GuiFlowDirection&  other)
{
	_stream << other.getValueName(other._value);
	return _stream;
}

inline std::istream& operator >> (std::istream& _stream, GuiFlowDirection&  other)
{
	std::string value;
	_stream >> value;
	other = GuiFlowDirection::parse(value);
	return _stream;
}

struct GuiMenuItemType
{
	enum Enum
	{
		Normal,
		Popup,
		Separator,
		MAX
	};

	GuiMenuItemType(Enum value = MAX)
		: _value(value)
	{
	}

	static GuiMenuItemType parse(const std::string& value)
	{
		GuiMenuItemType type;
		int iType = 0;
		for (;;)
		{
			const char* name = type.getValueName(iType);
			if (strcmp(name, "") == 0 || name == value)
				break;
			iType++;
		}
		type._value = Enum(iType);
		return type;
	}

	std::string print() const
	{
		return getValueName(_value);
	}

	int getValue() const
	{
		return _value;
	}

	const char* getValueName(int index) const
	{
		static const char* values[MAX + 1] = { "Normal", "Popup", "Separator", "" };
		return values[(index < MAX && index >= 0) ? index : MAX];
	}

private:
	Enum _value;
};

inline bool operator == (GuiMenuItemType const& a, GuiMenuItemType const& b)
{
	return a.getValue() == b.getValue();
}

inline bool operator != (GuiMenuItemType const& a, GuiMenuItemType const& b)
{
	return a.getValue() != b.getValue();
}

inline std::ostream& operator << (std::ostream& _stream, const GuiMenuItemType&  _value)
{
	_stream << _value.getValueName(_value.getValue());
	return _stream;
}

inline std::istream& operator >> (std::istream& _stream, GuiMenuItemType&  _value)
{
	std::string value;
	_stream >> value;
	_value = GuiMenuItemType::parse(value);
	return _stream;
}

_NAME_END

#endif