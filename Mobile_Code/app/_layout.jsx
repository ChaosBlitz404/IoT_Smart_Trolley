import { Stack } from 'expo-router';
import { Appearance, StatusBar, StyleSheet} from 'react-native';

import { QueryClient,QueryClientProvider } from '@tanstack/react-query';
import CoinSystem from '../global/globalcontext';

const client = new QueryClient();
export default function RootLayout() {
  const colorScheme = Appearance.getColorScheme();

  return (
    <CoinSystem>
      <QueryClientProvider client={client}>
        <StatusBar 
          barStyle={colorScheme === 'dark' ? 'light-content' : 'dark-content'}
          backgroundColor={colorScheme === 'dark' ? '#000' : '#fff'} 
        />
        <Stack>
          <Stack.Screen name='index' options={{
            headerShown : false
          }}/>
          <Stack.Screen name='(minigame)' options={{
            headerShown : false
          }}/>
          <Stack.Screen name='search/[query]' options={{
            headerShown : false

          }}/>
          <Stack.Screen name='item/[id]' options={{
            headerShown : true,
            title: "Product",
            headerTitleStyle:{
              fontWeight:'bold'
            }
          }}/>
          <Stack.Screen name='(product)' options={{
            headerShown : false
          }}/>
        </Stack>
      </QueryClientProvider>
    </CoinSystem>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
