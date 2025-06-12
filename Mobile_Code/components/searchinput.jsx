import { View, Text, TouchableOpacity, StyleSheet, TextInput, Alert } from 'react-native'
import React, { useEffect, useState } from 'react'
import SearchIcon from '../assets/images/SearchIcon'
import { router, usePathname } from 'expo-router'

const SearchInput = ({initialQuery}) => {

    const [Query, setQuery] = useState(initialQuery || "")



  return (
    <View style={styles.box}>
        <TouchableOpacity
            onPress={() => {

                if(!Query){
                    return Alert.alert("Missing Value","Please Input a Value")
                }
                else{
                    return router.push(`/search/${Query}`)
                }

            }}
        >
            <SearchIcon
                style={styles.iconSearch}
                resizeMode='contain'/>
        </TouchableOpacity>

      <TextInput
        style={styles.inputTxt}
        value={Query}
        placeholder='Search Item..'
        onChangeText={(e) => setQuery(e)}

      />
    </View>
  )
}

export default SearchInput

const styles = StyleSheet.create({

    box : {
      backgroundColor:'white',
      padding:10,
      borderRadius:10,
      display:'flex',
      flexDirection: 'row',
      gap:20,
      alignItems:'center',
      margin:5,

    },
    iconSearch : {
      width:10,
      height:10
    }

  
  })