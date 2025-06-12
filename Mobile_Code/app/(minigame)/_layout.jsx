import React from 'react'
import { Stack } from 'expo-router'

const MinigameLayout = () => {
  return (
    <Stack>
        <Stack.Screen
            name="game"

            options={{
                headerShown:true,
                title:"Top Up",
                headerTitleStyle:{
                  fontWeight:'bold'
                }
            }}
        />
    </Stack>
  )
}

export default MinigameLayout