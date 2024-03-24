import UserInfoBean from '../Common/Bean/UserInfoBean'
import router from '@ohos.router';

@Entry
@Component
struct UseInfoShow{
  @State user: UserInfoBean = new UserInfoBean("老张","fufu",[]);

  @Builder ElementShow(name: String, detail: any) {
    Row() {
      Text(`${name}`)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
      Text(`${detail}`)
        .fontSize(30)

    }
    .width('95%')
    .justifyContent(FlexAlign.SpaceBetween)

    Divider()
      .width('95%')
  }

  build(){
    Column(){
      Column(){
        Text('个人信息')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .width('95%')
      .margin(20)

      Column(){
        Divider()
          .width('95%')
        this.ElementShow("用户名",this.user.Username)
        this.ElementShow("头像",this.user.Username)
        this.ElementShow("管理的农田",this.user.UserFarm)
      }

      Column(){
        Text("<  返回")
        .fontSize(20)
        .height('120%')
        .onClick(()=>{
          router.back({
            url: 'pages/MainPage'
          })
        })
      }
    }
    .height('100%')
    .backgroundColor('#f1f2f3')
  }
}