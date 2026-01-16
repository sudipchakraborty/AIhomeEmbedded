#include <Arduino.h>
#include "EventsSEQ.h"
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief  this is the constructor of EventsSEQ class
 * @param param1 NA
 * @param param2 NA
 * @return  NA
 */
 EventsSEQ::EventsSEQ(){
 }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief  this function initialize the EventsSEQ class
 * @param void
 * @return void
 */
 void EventsSEQ::begin(void){
    buffer_reset();
 }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief  this function initialize the EventsSEQ class
 * @param void
 * @return void
 */
 void EventsSEQ::buffer_reset(void){
    index=0;
    for (byte i=0;i<BUFFER_SIZE;i++){
        buffer[i]=0;
    }
 }
//_____________________________________________________________________________________________________________________________________________________________________
// /**
//  * @brief  this function initialize the EventsSEQ class
//  * @param void
//  * @return void
//  */
//  void EventsSEQ::buffer_reset(void){
//     index=0;
//     for (byte i=0;i<BUFFER_SIZE;i++){
//         buffer[i]=0;
//     }
//  }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this function add a value to the event buffer  
 * @param  val  value to be added to the buffer
 * @return void
 */
 void EventsSEQ::push(byte val){
    if(index<BUFFER_SIZE){
        buffer[index]=val;
        index++;
    }
 }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief  this function initialize the EventsSEQ class
 * @param void
 * @return void
 */
 String EventsSEQ::get_buffer_as_string(void){
    String str="";
    for (byte i=0;i<index;i++){
        str+=String(buffer[i]);
        if(i<index-1){
            str+=",";
        }
    }
    return str;
 }
//_____________________________________________________________________________________________________________________________________________________________________






