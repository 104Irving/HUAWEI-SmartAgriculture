import UserInfoBean from '../Common/Bean/UserInfoBean';
import { InfoItem, MineItemList } from '../model/MineItemList';
import router from '@ohos.router';

@Component
export struct MineComponent {
  @State nickname: string = 'Jerry'; // 昵称
  @State signature: string = 'nothing to be told';//签名
  // @State showcase: boolean[] = [false, false, false, false, false]//组件是否显示

  build(){
    Column(){
      Column(){
        Text(this.nickname)
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
        Text(this.signature)
          .fontSize(14)
          .fontColor(Color.Orange)
      }
      .width('95%')
      .margin(20)

      //功能列表
      Column(){
        List(){
          ForEach(MineItemList,(item:InfoItem)=>{
            ListItem(){
              //Text(item.title)
              Row(){
                Row(){
                  Text(item.title)
                    .fontSize(22)
                    .onClick(()=>{
                      router.pushUrl({
                        url:`pages/${item.url}`
                      })
                    })
                }
              }
              .width('100%')
              .height(52)
              .justifyContent(FlexAlign.SpaceBetween)
            }
            .border({
              width: {bottom:1},
              color:Color.Orange
            })

          },item=>JSON.stringify(item))
        }
        .margin(10)
        .border({
          radius:{
            topLeft:24,
            topRight:24
          }
        })
        .backgroundColor('#115f7691')
        .width('100%')
        .height('90%')

      }
      .width('95%')

    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')
  }
}

