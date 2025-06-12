import { View, Text, StyleSheet, Touchable, TouchableOpacity } from 'react-native'
import React from 'react'

const CustomButton = ({title,handlePress,additionalStyle,textStyle}) => {
  return (
    <TouchableOpacity 
      style={[styles.border,additionalStyle]}
      onPress={handlePress}  
    >
      <Text style={[styles.insidetxt,textStyle]}>{title}</Text>
    </TouchableOpacity>
  )
}

export default CustomButton

const styles = StyleSheet.create({
  border:{
    borderRadius:10,
    padding:10,
    display:'flex',
    alignItems:'center',
    justifyContent:'center',
    width:335
    
  },
  insidetxt :{
    textAlign:'center',
    color:'white',
    fontWeight:'bold',
    fontSize:20
  }
})