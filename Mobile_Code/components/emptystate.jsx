import { View, Text, StyleSheet } from 'react-native'
import React from 'react'

const EmptyState = ({title}) => {
  return (
    <View style={styles.bigBox}>
      <Text style={styles.bigTxt}>{title}</Text>
    </View>
  )
}

export default EmptyState

const styles = StyleSheet.create({
  bigTxt : {
    fontSize:40,
    textAlign:'center',
    color:'gray'

  },
  bigBox :{
    height:500,
    display:'flex',
    flexDirection:'row',
    alignItems:'center',
    justifyContent:'center'
  }
})