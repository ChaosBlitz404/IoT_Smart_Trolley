import { View, Text, StyleSheet, FlatList, Image, TouchableOpacity, RefreshControl, ActivityIndicator } from 'react-native'
import React, { useState } from 'react'
import { SafeAreaView } from 'react-native-safe-area-context'
import ProductButton from '../../components/productbutton'
import image from '../../assets/constants/image'
import ProductCard from '../../components/productcard'
import EmptyState from '../../components/emptystate'
import GridViewIcon from '../../assets/images/GridViewIcon'
import { router, useLocalSearchParams } from 'expo-router'
import ListViewIcon from '../../assets/images/ListViewIcon'
import HorizontalCard from '../../components/horizontalcard'
import SearchInput from '../../components/searchinput'
import { getProductByTitle } from '../../library/fetch'
import { useQuery } from '@tanstack/react-query'
import { useGlobalContext } from '../../global/globalcontext'
import CustomButton from '../../components/custombutton'

const Search = () => {

  const {Coin} = useGlobalContext()
  const {query} = useLocalSearchParams()
  const [Grid, setGrid] = useState(false)
  console.log("current :" + query)

  const {data,isLoading, isError, error  } = useQuery({
    queryKey: ['productTitle',query],
    queryFn: () => getProductByTitle(query)});


  return (
    <SafeAreaView style={styles.safeArea}>
      
        <View style={styles.headerArea}>
          <SearchInput initialQuery={query}/>
          <View style={styles.miniFlex}>
            <ProductButton title="My Products"/>
            <CustomButton 
              textStyle={styles.homeTxt}
              additionalStyle={styles.backHome}
              title="Home" 
              handlePress={()=>router.push("/")}/>
          </View>

          <View style={styles.boxCoin}>
            <Text numberOfLines={1} style={styles.textCoin}>{Coin}</Text>
            <Text style={styles.coin}>My Coins</Text>
          </View>

          <TouchableOpacity 
            style={styles.egg}
            onPress={() => {router.push('/game')}}
            activeOpacity={0.6}
          >
            <Image
              source={image.fullEgg}
              style={styles.fullEgg}

            />
          </TouchableOpacity>
          
        </View>
        <View style={styles.flatListView}>
          {Grid? (
            <FlatList
              style={styles.bigList}
              data = {data}
              numColumns={2}
              key={['A']}
              keyExtractor = {(item) => item.id}
              renderItem = {({item}) => 
                (<ProductCard product={item}/>)

              }
              ListHeaderComponent = {() => (
                <View style={styles.topPart}>
                  <Text style={styles.bigTxt}>Search Results</Text>

                  {Grid ? ( 
                      <TouchableOpacity
                        onPress={() => setGrid(false)}
                        activeOpacity={0.6}
                      >
                        <GridViewIcon/>
                      </TouchableOpacity>):(
                    
                      <TouchableOpacity
                        onPress={() => setGrid(true)}
                        activeOpacity={0.6}
                      >
                        <ListViewIcon/>
                      </TouchableOpacity>)
                  }
                </View>
            )}
            ListEmptyComponent = {() => {
              return isLoading? (<ActivityIndicator size="large" color="#0000ff" animating={true}/>) : (<EmptyState title="No Product Found" />)
            }}
          />
          ): (
              <FlatList
              style={styles.bigList}
              data = {data}
              key={['B']}
              numColumns={1}
              keyExtractor = {(item) => item.id}
              renderItem = {({item}) => 
                (<HorizontalCard product={item}/>)

              }
              ListHeaderComponent = {() => (
                <View style={styles.topPart}>
                  <Text style={styles.bigTxt}>Search Results</Text>

                  {Grid ? ( 
                      <TouchableOpacity
                        onPress={() => setGrid(false)}
                        activeOpacity={0.6}
                      >
                        <GridViewIcon/>
                      </TouchableOpacity>):(
                    
                      <TouchableOpacity
                        onPress={() => setGrid(true)}
                        activeOpacity={0.6}
                      >
                        <ListViewIcon/>
                      </TouchableOpacity>)
                  }
                

                </View>
              )}
              ListEmptyComponent = {() => {
                return isLoading? (<ActivityIndicator size="large" color="#0000ff" animating={true}/>) : (<EmptyState title="No Product Found" />)
              }}
          />
          )}
        </View>
          

    </SafeAreaView>
  )
}

export default Search

const styles = StyleSheet.create({
  homeTxt :{
    color:'black',
    textAlign:'center',
    fontSize:18,

  },
  backHome : {
    backgroundColor:'white',
    marginTop:5,
    width:80,
    height:44,
    padding:10,
    display:'flex',
    alignItems:'center',
    justifyContent:'center'
  },
  miniFlex : {
    display:'flex',
    flexDirection:'row',
    alignItems:'flex-start',
    justifyContent:'flex-start'
  },
  flatListView :{
    height:'100%'
  },
  safeArea : {
    height:'100%',
    backgroundColor: 'purple',
  },
  headerArea : {
    backgroundColor: 'purple',
    padding: 10
  },
  bigList : {
    backgroundColor:'white',
    borderRadius:10,
    padding:20,
    borderBottomLeftRadius:0,
    borderBottomRightRadius:0,
  },
  bigTxt : {
    fontSize:30,
    fontWeight: 'bold',
  },
  topPart : {
    display:'flex',
    flexDirection:'row',
    alignItems:'center',
    justifyContent:'space-between',
    margin:0,

  },
  boxCoin : {
    position:'absolute',
    backgroundColor:'white',
    top :90,
    left:270,
    zIndex: 5,
    borderRadius:10,
    paddingHorizontal: 15,
    paddingVertical:8,
    alignItems:'flex-end',
    elevation: 10,
    shadowColor: '#000', 
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10,
    width:100,

  },
  textCoin:{
    fontSize:25,
    fontWeight:'900',
    color:'purple'
  },
  coin : {
    color:'gray'
  },
  egg :{
    position:'absolute',
    width:60,
    height:60,
    left:300,
    top:700,
    zIndex:5,
    backgroundColor:'white',
    borderRadius:'50%',
    alignItems:'center',
    justifyContent:'center',
    elevation:10,
    shadowColor: '#000', 
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10,
  },
  fullEgg : {
    width:28,
    height:35,
  }
});