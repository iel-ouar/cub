#include "cub.h"


int key_press(int keycode, t_btn *btn)
{
	if (keycode == W)
		btn->btn_w = true;
	else if (keycode == A)
		btn->btn_a = true;
	else if (keycode == S)
		btn->btn_s = true;
	else if (keycode == D)
		btn->btn_d = true;
	else if (keycode == L)
		btn->btn_l = true;
	else if (keycode == R)
		btn->btn_r = true;
	return (0);
}

int key_release(int keycode, t_btn *btn)
{
if (keycode == W)
		btn->btn_w = false;
	else if (keycode == A)
		btn->btn_a = false;
	else if (keycode == S)
		btn->btn_s = false;
	else if (keycode == D)
		btn->btn_d = false;
	else if (keycode == L)
		btn->btn_l = false;
	else if (keycode == R)
		btn->btn_r = false;
	return (0);
}

bool	check_pressing(t_btn *btn)
{
	if (btn->btn_w || btn->btn_a || btn->btn_s
		|| btn->btn_d || btn->btn_l || btn->btn_r)
		return (true);
	return (false);
}