/*
 * CommandMeasure.h
 *
 *  Created on: Dec 4, 2020
 *      Author: martin
 */

#ifndef COMMANDMEASURE_H_
#define COMMANDMEASURE_H_

int InitMeasureCommandHandler(void);
int MeasureCommandHandler(int16_t dev_nr,uint8_t *command,int len);

#endif /* COMMANDMEASURE_H_ */
