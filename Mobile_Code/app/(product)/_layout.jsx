import { View, Text } from 'react-native'
import React from 'react'
import { Stack } from 'expo-router'

const ProductLayout = () => {
  return (
    <Stack>
        <Stack.Screen 
          name="cart" 

          options={{
            headerShown:true,
            title:"Check Out",
            headerTitleStyle:{
              fontWeight:'bold'
            }
        }}/>
    </Stack>
  )
}

export default ProductLayout