#ifndef PELCOD_H
#define PELCOD_H

#define PELCOD_MSG_SIZE		7

typedef int (*Funcptr_t)(unsigned char*, int);

/*globally used functions */
void pelcod_init(Funcptr_t ptr);

/* Pelcod standard protocol */
int pelcod_move_right(unsigned char address, unsigned short speed);
int pelcod_move_left(unsigned char address, unsigned short speed);
int pelcod_move_up(unsigned char address, unsigned short speed);
int pelcod_move_down(unsigned char address, unsigned short speed);
int pelcod_zoom_far(unsigned char address);
int pelcod_zoom_near(unsigned char address);

int pelcod_move_stop(unsigned char address);

/* Pelcod extended protocol */
int pelcod_goto_preset(unsigned char address, unsigned short preset);
int pelcod_set_zoom_speed(unsigned char address, unsigned short speed);
int pelcod_set_focus_speed(unsigned char address, unsigned short speed);
int pelcod_move_around(unsigned char address);
int pelcod_write_str(unsigned char address, const unsigned char* str);
#endif // PELCOD_H
