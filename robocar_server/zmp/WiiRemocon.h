#include "types.h"

#include <cwiid.h>

#pragma pack(push, 1)
struct WiimState {
	int connection;
	ulong input_btn;
	int acc_x;
	int acc_y;
	int acc_z;

	int rumble_enable;
	int led_pattern;
};
#pragma pack(pop)

class WiiRemocon
{
	friend cwiid_mesg_callback_t cwiid_callback;
	friend cwiid_err_t err_handler;

public:
	WiiRemocon();
	~WiiRemocon();

public:
	// primary functions.
	bool WaitConnection();
	bool UpdateRequest();
	void Term();

	// secondary functions.
	bool Open();
	
	// getter
	ulong GetButton() const;
	void GetAcc(int *ax, int *ay, int *az) const;

	// setter
	bool SetLed(uchar led_pattern);
	bool SetRumble(bool enable);

protected:

private:
	cwiid_wiimote_t *_wiimote;
	static WiimState *s_wiim_state;
	
	bool _b_primary;

	uchar _current_led_pattern;
	bool _current_rumble_enable;
};


