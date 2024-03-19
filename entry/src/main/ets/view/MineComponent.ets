import { InfoItem, MineItemList } from '../model/MineItemList';

@Component
export struct MineComponent {
  @State nickname: string = 'Jerry'; // 昵称
  @State signature: string = '在大大的花园里面挖呀！挖呀！挖！';//签名

  build(){
    Column(){
      //Text('用户信息')
      //用户基本信息
      Column(){
        // Image($r('app.media.user_avtar'))
        //   .width(68)
        //   .height(68)
        //   .borderRadius(34)
        Text(this.nickname)
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
        Text(this.signature)
          .fontSize(14)
          .fontColor(Color.Orange)


      }.width('95%')
      .margin(20)

      //功能列表
      Column(){

        List(){
          ForEach(MineItemList,(item:InfoItem)=>{
            ListItem(){
              //Text(item.title)
              Row(){
                Row(){
                  // Image(item.icon)
                  //   .width(38)
                  //   .height(38)
                  Text(item.title)
                    .fontSize(22)
                }
                // Image($r('app.media.right'))
                //   .width(38)
                //   .height(38)
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