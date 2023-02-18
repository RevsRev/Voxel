#pragma once

template <typename T, typename U, typename V>
class Triple {
public:
	T first;
	U second;
	V third;

public:
	Triple(T first, U second, V third) {
		this->first = first;
		this->second = second;
		this->third = third;
	}

	bool operator==(const Triple& rhs) const
	{
		return first == rhs.first && second = rhs.second && third = rhs.third;
	}
	bool operator!=(const Triple& rhs) const
	{
		return !(this == rhs);
	}

	bool operator<(const Triple& rhs) const
	{
		if (first < rhs.first) {
			return true;
		}
		else if (first > rhs.first) {
			return false;
		}

		if (second < rhs.second) {
			return true;
		}
		else if (second > rhs.second) {
			return false;
		}

		if (third < rhs.third) {
			return true;
		}
		return false;
	}
	bool operator <=(const Triple& rhs) const
	{
		return this == rhs || this < rhs;
	}

	bool operator >(const Triple& rhs) const
	{
		return !(this <= rhs);
	}
	bool operator >=(const Triple& rhs) const
	{
		return !(this < rhs);
	}
};