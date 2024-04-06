import UserInfoBean from '../Common/Bean/UserInfoBean'
import router from '@ohos.router';

@Entry
@Component
struct AccountSecurity{
  @State user: UserInfoBean = new UserInfoBean("老张",0,[]);

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
      Text('个人信息')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
      Divider()
        .width('95%')
      this.ElementShow("用户名",this.user.Username)
      this.ElementShow("头像",this.user.Username)
      this.ElementShow("管理的农田",this.user.UserFarmList)


      Text("<  返回")
        .fontSize(20)
        .height('300%')
        .onClick(()=>{
          router.back({
            url: 'pages/MainPage'
          })
        })

    }.height('50%')
  }
}