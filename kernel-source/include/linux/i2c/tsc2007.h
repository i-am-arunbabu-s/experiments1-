#ifndef __LINUX_I2C_TSC2007_H
#define __LINUX_I2C_TSC2007_H

/* linux/i2c/tsc2007.h */

struct tsc2007_platform_data {
	u16	model;						/* 2007. */
	u16	x_plate_ohms;				/* must be non-zero value */
	u16	max_rt; 					/* max. resistance above which samples are ignored */
	
	unsigned long sample_delay;		/* delay (in ms) between samples */
	unsigned long report_delay; 	/* delay (in ms) between sample and touch report */
	unsigned long initial_delay;	/* delay (in ms) before sampling begins */
	
	int	fuzzx; 						/* fuzz factor for X, Y and pressure axes */
	int	fuzzy;
	int	fuzzz;

	int	(*get_pendown_state)(void);
	void	(*clear_penirq)(void);		/* If needed, clear 2nd level interrupt source */
	
	int	(*init_platform_hw)(void);
	void	(*exit_platform_hw)(void);
};

#endif
