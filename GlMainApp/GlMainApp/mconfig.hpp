#pragma once
class Setting
{
	enum enumSetting { eBitDepth, eFullScreen, eWidth, eHight, eMAX };
public:

	Setting()
	{
		setColor_32();
		setFullScreen(false);
		setWH(800, 600);
	}

	void setColor_16() { set(eBitDepth, 16); }
	void setColor_32() { set(eBitDepth, 32); }
	int getColor() { return get(eBitDepth); }
	void setFullScreen(bool t = false) { set(eFullScreen, t ? 1 : 0); }
	bool isFull() { return 1 == get(eFullScreen); }
	void setWH(int w, int h) { set(eWidth, w); set(eHight, h); }
	int getWidth() { return get(eWidth); }
	int getHight() { return get(eHight); }

private:

	inline void set(enumSetting e, int v) { settings[e] = v; }
	inline int get(enumSetting e) { return settings[e]; }

	int settings[eMAX];
};
