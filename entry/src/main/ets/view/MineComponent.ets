import UserInfoBean from '../Common/Bean/UserInfoBean';
import { InfoItem, MineItemList } from '../model/MineItemList';
import router from '@ohos.router';

@Component
export struct MineComponent {
  @State user: UserInfoBean = new UserInfoBean("傻FUFU","fufu",[]);
  @State signature: string = '是歌姬吧';//签名

  build(){
    Column(){
      Row(){
        Image($r('app.media.fufu'))
          .width(100)
          .height(100)
          .margin(20)

        Column(){
          Text(this.user.Username)
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Start)
            .margin(20)
          Text(`签名:${this.signature}`)
            .fontSize(14)
            .fontColor(Color.Orange)
            .textAlign(TextAlign.Start)
        }
        .justifyContent(FlexAlign.SpaceBetween)

      }
      .width('95%')
      .margin(10)

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

