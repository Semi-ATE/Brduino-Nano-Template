/*
 * CmdInfo.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef CMDINFO_H_
#define CMDINFO_H_

int InitInfoCommandHandler(void);
int InfoCommandHandler(int16_t dev_nr,uint8_t *command,int len);

#endif /* CMDINFO_H_ */
