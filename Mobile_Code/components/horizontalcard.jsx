import { View, Text, Image, StyleSheet, TouchableOpacity } from 'react-native'
import React from 'react'
import { router } from 'expo-router'

const HorizontalCard = ({product,quantity}) => {

  const { id,title, image, price} = product
  return (
    <TouchableOpacity style={styles.box}
      onPress={() => router.push(`/item/${id}`)}>
      <View style={styles.innerDisplay}>
        <Image
          source={{uri: image}}
          style={styles.imageThing}
          resizeMode='contain'
        />
        <View style={styles.horiz}>
          <Text style={styles.titleTxt} numberOfLines={2}>{title}</Text>
          <Text>Rp {price}</Text>
        </View>
      </View>

      <View style={styles.rightQty}>
        <Text>x{quantity}</Text>
      </View>

    </TouchableOpacity>
  )
}

export default HorizontalCard

const styles = StyleSheet.create({
  rightQty : {
    marginRight:15
  },
  innerDisplay : {
    display:'flex',
    flexDirection:'row',
    gap:10
  },
  box:{
    backgroundColor:'white',
    height:80,
    width:350,
    display:'flex',
    flexDirection:'row',
    justifyContent:'space-between',
    alignItems:'center',
    padding:10,
    marginVertical:15,
    marginRight:10,
    borderRadius:10,
    elevation:10,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10, 
    gap:10


  },
  horiz :{
    display:'flex',
    flexDirection:'column',
    maxWidth:225
  },    
  titleTxt :{
    fontWeight:'bold',
    fontSize:17
  },
  imageThing:{
    width:60,
    height:60
  }
})